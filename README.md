# Intruder Detection System (ESP32)
📌 Beginner IoT/Embedded Systems Project
This project is part of my learning journey at Nithub, University of Lagos, where I’m building practical skills in microcontrollers and sensors..

---

## 🚨 Project Overview

An intruder detection system using an ESP32 microcontroller with:
Ultrasonic sensor (distance/movement detection)
Buzzer or vibration motor (intruder alert)
When someone enters a defined range, the system triggers an alarm. Once the area is clear, the alarm resets automatically.

---

## 🛠 Components Used
- ESP32
- Ultrasonic Sensor (HC-SR04 or similar)
- Breadboard + jumper wires
- Buzzer or vibration motor
- USB Power supply

---

## ⚙️ How It Works
1. The ultrasonic sensor measures distance via trigger/echo pins.
2. If the measured distance falls below a threshold (e.g., < 6 cm), the system considers it an "intruder."
3. The buzzer/vibration motor turns ON to alert.
4. Once the area is clear (e.g., distance > 8 cm), the system resets.

---

## 📂 Project Structure
```
intruder-detection-system/
│
├── src/
│   └── Program.cpp   # The Arduino/ESP32 code
│
├── test/              # Unit/functional tests (future)
├── paltform.ini       # Build config
│
├── docs/
│   └── setup_guide.md      # Step-by-step setup notes
│
├── README.md               # Main project description
├── LICENSE                 # (MIT recommended)
├── .gitignore
```


---

## 📸 Demo
[Intruder Detection Setup](docs/setup.jpg)  
(Picture of ESP32 + ultrasonic sensor + vibration motor on breadboard)

🎥 (Optional: short video/GIF demo link here)
---

## 🔮 Future Extensions
- Send alerts via Firebase
- Trigger webhooks for IoT dashboards
- Integrate with a mobile control app
---

## 📚 Learning Notes
- This project marks the start of my IoT journey:

- Exploring embedded systems with ESP32

- Gaining hands-on practice with sensors and actuators

- Building confidence through small but functional IoT prototypes

