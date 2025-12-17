# ESP-32_RC_Car
ESP32 Bluetooth RC Car: A 4-wheel remote-controlled car using ESP32 and dual L298N motor drivers, controllable via Bluetooth. Supports forward, backward, left, right, and stop commands. Compatible with apps like RC Bluetooth Car Control. Demo video &amp; photos included.
#  ESP32 Bluetooth RC Car

Control a 4‑wheel RC car using **ESP32** via **Bluetooth**. Supports forward, backward, left, right, and stop commands. Features dual L298N motor drivers for smooth motion and optional PWM speed control.

 **Demo video & photos:**  
https://drive.google.com/drive/folders/1ogZ4_yY6Qj4JNATNIe1tZ4YzO1di0dCy?usp=drive_link

---

##  Project Description

The **ESP32 Bluetooth RC Car** is a remote‑controlled vehicle that uses an **ESP32** microcontroller and **Bluetooth Serial** to receive commands from a smartphone or PC. It drives four wheels with dual L298N motor drivers and mirrors signals to a secondary driver for synchronized motion. Simple Bluetooth characters control movement, and PWM speed control allows smooth driving.

You can use **any Bluetooth RC car control app** (like **RC Bluetooth Car Control**) to send commands directly from your smartphone. ⚠️ Make sure the app is paired with `ESP32_RC_Car`.

---

##  Features
- Bluetooth control via smartphone/PC  
- Dual L298N motor drivers (Main + Secondary)  
- Forward, backward, left, right & stop  
- PWM motor speed control  
- Compatible with RC Bluetooth control apps

---

##  Controls
Send these characters via Bluetooth (from app or PC):
- **F** – Move Forward  
- **B** – Move Backward  
- **L** – Turn Left  
- **R** – Turn Right  
- **S** – Stop Motors  

---

## 🛠 Hardware Connections

| Pin | Connection | Function |
|-----|------------|----------|
| 26  | IN1        | Left Motor Forward |
| 27  | IN2        | Left Motor Backward |
| 14  | IN3        | Right Motor Forward |
| 12  | IN4        | Right Motor Backward |
| 25  | ENA        | Left Motor PWM |
| 13  | ENB        | Right Motor PWM |
| 16  | SEC_IN1    | Secondary Forward Left |
| 17  | SEC_IN2    | Secondary Backward Left |
| 5   | SEC_IN3    | Secondary Forward Right |
| 18  | SEC_IN4    | Secondary Backward Right |
| 19  | SEC_ENA    | Secondary Left PWM |
| 21  | SEC_ENB    | Secondary Right PWM |

---

##  How to Run
1. Open Arduino IDE with ESP32 support installed.  
2. Connect ESP32 to your PC.  
3. Upload the code.  
4. Pair your phone with **RC Bluetooth Car Control** (or any compatible app) using the device name `ESP32_RC_Car`.  
5. Send control commands (F, B, L, R, S) via the app.

---

##  Notes
- Adjust `MOTOR_SPEED` (0–255) in the code for speed control.  
- Make sure EN pins are set up for PWM or just connected to high if you want speed modulation.  
- Test on a safe surface before full operation.  
- The secondary motor driver is optional the car can functtion even with only one driver.

---

##  Disclaimer
This project is for **education and fun** only.  
It does **not replace professional robotics hardware or safety guidelines**.
