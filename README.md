# 🤖 Arduino Line Following Robot

This project demonstrates how to build a simple line-following robot using an Arduino Uno and a TCRT5000 sensor array.

It is a beginner-friendly robotics project that covers motor control, sensor reading, and basic PID algorithm implementation.

---

## 📺 Demo

🎥 Watch the full tutorial on YouTube:  
(Insert your video link here)

---

## 🧰 Components Used

- Arduino Uno  
- L298N Motor Driver Module  
- TCRT5000 5-Channel Sensor Module  
- 2x DC Geared Motors  
- Acrylic Robot Chassis  
- 2x 18650 Batteries  
- Jumper Wires  

---

## ⚙️ Features

- Line detection using TCRT5000 sensors  
- Motor control via L298N  
- Basic PID algorithm for smooth line tracking  
- Adjustable parameters for tuning performance  

---

## 🔌 Wiring Overview

### Motor Driver (L298N → Arduino)

| L298N Pin | Arduino Pin |
|----------|------------|
| ENA      | 9          |
| ENB      | 10         |
| IN1      | 8          |
| IN2      | 7          |
| IN3      | 12         |
| IN4      | 13         |

### Sensor Module (TCRT5000 → Arduino)

| Sensor Pin | Arduino Pin |
|-----------|------------|
| OUT1      | 2          |
| OUT2      | 3          |
| OUT3      | 4          |
| OUT4      | 5          |
| OUT5      | 6          |

### Power

- Battery (+) → L298N 12V  
- Battery (–) → GND  
- L298N 5V → Arduino VIN  
- GND → GND  

---

## 🧠 How It Works

The robot uses 5 infrared sensors to detect a black line on a light surface.

- Sensors read the position of the line  
- A PID controller calculates the error  
- Motor speeds are adjusted accordingly  
- The robot stays aligned with the line  
