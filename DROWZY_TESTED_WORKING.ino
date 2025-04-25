#include <Wire.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <math.h>

// Wi-Fi credentials
const char* ssid = "GalaXy M118416 ANANYA";
const char* password = "avh22222";

// Firebase details
const String firebaseHost = "https://driver-drowziness-detection-default-rtdb.firebaseio.com/";
String driverID = "D001";

// Pins
#define IR_SENSOR_PIN 5
#define BUZZER_PIN 18
#define LED_PIN 23

// MPU6050
const int MPU_addr = 0x68;
const float pitchThreshold = 30.0;

// Timers
unsigned long eyeClosedStart = 0;
const unsigned long drowsyThreshold = 5000; // 5 sec
bool alertTriggered = false;

void setup() {
  Serial.begin(115200);

  pinMode(IR_SENSOR_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B); // power management
  Wire.write(0);    // wake up MPU6050
  Wire.endTransmission(true);

  // Wi-Fi connect
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500); Serial.print(".");
  }
  Serial.println(" Connected!");

  configTime(0, 0, "pool.ntp.org", "time.nist.gov");
}

void loop() {
  // --- IR SENSOR ---
  int eyeStatus = digitalRead(IR_SENSOR_PIN);  // HIGH = closed, LOW = open
  bool eyeClosed = (eyeStatus == HIGH);
  unsigned long currentTime = millis();

  // --- MPU6050 ---
  int16_t AcX, AcY, AcZ;
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr, 6, true);
  AcX = Wire.read() << 8 | Wire.read();
  AcY = Wire.read() << 8 | Wire.read();
  AcZ = Wire.read() << 8 | Wire.read();

  float ax = AcX / 16384.0;
  float ay = AcY / 16384.0;
  float az = AcZ / 16384.0;

  float pitch = atan2(ax, sqrt(ay * ay + az * az)) * 180.0 / PI;
  Serial.print("Pitch: "); Serial.println(pitch);

  bool headNodding = abs(pitch) > pitchThreshold;

  // --- Drowsiness Detection ---
  bool drowsy = false;

  if (eyeClosed) {
    if (eyeClosedStart == 0) {
      eyeClosedStart = currentTime;
    }
    if ((currentTime - eyeClosedStart >= drowsyThreshold)) {
      drowsy = true;
    }
  } else {
    eyeClosedStart = 0;
  }

  if (drowsy || headNodding) {
    if (!alertTriggered) {
      Serial.println("DROWSINESS DETECTED 🚨");
      digitalWrite(BUZZER_PIN, HIGH);
      digitalWrite(LED_PIN, HIGH);
      sendToFirebase(true);
      alertTriggered = true;
    }
  } else {
    Serial.println("Normal state");
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(LED_PIN, LOW);
    if (alertTriggered) {
      sendToFirebase(false);
      alertTriggered = false;
    }
  }

  delay(500);
}

void sendToFirebase(bool isDrowsy) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    String url = firebaseHost + "/drivers/" + driverID + ".json";
    String payload = "{\"drowsy\":" + String(isDrowsy ? "true" : "false") +
                     ",\"timestamp\":\"" + getTimeStamp() + "\"}";

    http.begin(url);
    http.addHeader("Content-Type", "application/json");

    int httpCode = http.PUT(payload);

    if (httpCode > 0) {
      Serial.println("Firebase Response: " + http.getString());
    } else {
      Serial.println("Firebase Error: " + String(httpCode));
    }

    http.end();
  } else {
    Serial.println("WiFi not connected");
  }
}

String getTimeStamp() {
  time_t now;
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) return "NA";
  char buf[20];
  strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &timeinfo);
  return String(buf);
}
