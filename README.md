# 💤 Driver Drowsiness Detection System 🚗 
The Driver Drowsiness Detection System is a smart safety solution designed to monitor a driver's alertness in real-time and help prevent road accidents caused by fatigue or drowsiness. The system uses a combination of hardware components and Python-based software to detect signs of drowsiness such as eye closure and head nodding. When drowsiness is detected, an immediate alert is triggered via a buzzer to wake up the driver and ensure road safety.

🛠️ Technologies & Tools
Hardware Components:

➤ ESP32 Microcontroller

➤ IR Eye Blink Sensor

➤ Accelerometer (e.g., MPU6050)

➤ Buzzer/Alarm

➤ USB Cable and Power Supply

Software & Tools:

➤ Python (for serial communication and alert logic)

➤ Firebase (for real-time data storage and driver monitoring)

➤ Google App Password (for sending email alerts)

➤ Arduino IDE (for ESP32 programming)

➤ Firebase Admin SDK

➤ Pyrebase / HTTP Requests for Firebase

➤ Email SMTP module

⚙️ Features

👁️ Eye Blink Detection: Uses an IR sensor to monitor eye blinks and detect prolonged eye closure.

🧠 Head Movement Detection: Detects head nodding or unnatural motion using an accelerometer.

🔔 Real-Time Alerts: Triggers a buzzer alarm when signs of drowsiness are detected.

📊 Dashboard Monitoring: Driver status and alerts are updated to Firebase for centralized monitoring.

📩 Email Notifications: Sends an email alert to authorities or family when drowsiness is detected.

👥 Multi-Driver Support: Scalable to monitor multiple drivers in real-time.

🔒 Authority Access: Secure login for authorized personnel to view drowsiness logs and take actions.

🧪 How It Works

1. The IR Sensor detects the frequency and duration of eye blinks.

2. The Accelerometer monitors the driver’s head tilt or abnormal nodding patterns.

3. When drowsiness is suspected:

▸ A buzzer is activated to alert the driver.

▸ A status update is sent to Firebase.

▸ An email notification is sent using the driver's ID and timestamp.

4. The dashboard updates the driver's condition in real-time, accessible to concerned authorities.

📦 Future Enhancements

📷 Integration with a camera and computer vision for more accurate face/eye monitoring.

🌐 GPS tracking of vehicle location during alerts.

📱 Mobile app integration for real-time driver status updates.

🧠 AI-based behavior analysis for predictive drowsiness alerts.

📁 Project Structure

```rust
├── Arduino/
│   ├── eye_blink_sensor.ino
│   └── accelerometer_code.ino
├── python/
│   ├── main.py
│   ├── firebase_integration.py
│   ├── email_alert.py
├── firebase/
│   └── firebase_config.json
├── README.md
└── LICENSE
```

🚀 How to Run
▸ Upload Arduino code to the ESP32 using Arduino IDE.

▸ Connect the sensors (IR + Accelerometer) and buzzer to ESP32 as per circuit diagram.

▸ Run main.py on your computer to start monitoring.

▸ Ensure Firebase credentials are correctly set up in the config file.

▸ Use Google App Password to enable email alerts if using Gmail.

