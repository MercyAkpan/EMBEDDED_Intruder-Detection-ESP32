# Intruder Detection System (ESP32)

📌 This project is part of my beginner learnings in IoT and embedded systems.  
I’m currently undergoing a program at **[NithubUnilag](https://nithub.unilag.edu.ng/)**, and this was one of the hands-on projects to build practical skills in microcontrollers and sensors.

---

## 🚨 Project Overview
This system uses an **ESP32** microcontroller with:
- Ultrasonic sensor (to detect distance/movement)
- Buzzer or vibration motor (to alert when an intruder is detected)

When someone enters a defined range, the system triggers an alarm.

---

## 🛠 Components Used
- ESP32
- Ultrasonic Sensor (HC-SR04 or similar)
- Breadboard + jumper wires
- Buzzer or vibration motor
- Power supply (USB)

---

## ⚙️ How It Works
1. The ultrasonic sensor measures distance using trigger/echo pins.
2. If the measured distance falls below a threshold (e.g., < 6 cm), the system considers it an "intruder."
3. The buzzer/vibration motor turns ON to alert.
4. Once the area is clear (e.g., distance > 8 cm), the system resets.

---

## 📂 Project Structure
```
intruder-detection-system/
│
├── src/
│   └── main.cpp   # The Arduino/ESP32 code
│
├── test/
├── paltform.ini
│
├── docs/
│   └── setup_guide.md      # Step-by-step setup notes
│
├── README.md               # Main project description
├── LICENSE                 # (optional, MIT recommended)
├── .gitignore
├── README.md               # Main project description
├── LICENSE                 # (optional, MIT recommended)
├── .gitignore
```


---

## 📸 Demo
![Intruder Detection Setup](docs/setup.jpg)  
*(Picture of a breadboard setup with ESP32 and sensor and the vibration motor)*

---

## 🔮 Future Extensions
- Send alerts via Firebase
- Trigger webhooks for IoT dashboards
- Control via mobile app

---

## 📚 Learning Notes
This project is part of my IoT learning journey:
- Finding my software inclinations in IoT
- Starting from embedded systems with ESP32
- Exploring practical microcontroller projects
