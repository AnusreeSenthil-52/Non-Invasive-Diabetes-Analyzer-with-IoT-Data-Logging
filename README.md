# 🫁 Non-Invasive-Diabetes-Analyzer-with-IoT-Data-Logging

A complete embedded + digital solution for early diabetes screening using breath acetone analysis. This project combines hardware (ESP32 + MQ3), a custom web interface (HTML/JS), real-time mobile integration (Blynk), cloud storage (Google Sheets), and automated medical file delivery (Elastic Email).

---

## 📌 Overview

- Detects acetone in exhaled breath using an MQ3 gas sensor
- Displays results on an LCD display and LED alerts
- Logs patient ID, ppm value, and result in Google Sheets
- Sends medical history files via email using a VS Code-based web interface
- Real-time display of results via Blynk IoT app

---

## 🛠️ Hardware Components

| Component           | Function                                         |
|---------------------|--------------------------------------------------|
| ESP32               | Main controller with WiFi                       |
| MQ3 Sensor          | Detects breath acetone levels                   |
| LCD 16x2 (I2C)      | Displays live readings and results              |
| 4x4 Matrix Keypad   | 3-digit Patient ID input                        |
| Buzzer              | Alerts based on severity                        |
| RGB LEDs            | Visual indicators (Normal, Mild, High)          |
| Exhaust Fan         | Clears residual gas after each test             |
| Buck Converter      | Voltage regulation                              |
| 9V Battery          | Power source                                    |

---

## 💻 Software Stack

| Tool/Platform         | Purpose                                              |
|-----------------------|------------------------------------------------------|
| Arduino IDE           | ESP32 firmware development                          |
| Google Apps Script    | Logs data to Google Sheets                          |
| HTML/CSS/JavaScript   | Web interface for patient form and file sending     |
| SMTP.js + Elastic Email| Email automation from web interface                |
| Blynk IoT             | Real-time remote monitoring                         |
| Google Sheets         | Permanent data storage                              |
| VS Code               | Frontend development                                |

---

## 📁 Files Included

| File/Folder                 | Description                                      |
|-----------------------------|--------------------------------------------------|
| `ArduinoCode.ino`          | Arduino code for ESP32 + sensor + display logic |
| `web_interface`            | VS Code-based frontend for patient data input   |
| `LogtoSheets.txt`          | Script to log data to Google Sheets             |
| `Results`                  | Hardware photos, LCD screenshots, result plots  |

---

## ✨ Key Features

- Non-invasive and portable
- Acetone-to-ppm conversion and classification (Normal, Mild, High)
- Logs every test with timestamp and result
- Sends patient data and medical file to doctor automatically
- Works with Blynk for real-time mobile display
- Exhaust system clears chamber for accurate repeated use

---

## 🧠 Skills Gained

- Embedded systems (ESP32, I2C devices, MQ gas sensors)
- Web development (HTML, CSS, JavaScript)
- API integration (SMTP.js, Elastic Email)
- Data automation with Google Apps Script
- Real-time mobile IoT display (Blynk)
---

## 🔮 Future Developments

- Add MQ-138 sensor for higher acetone sensitivity
- Integrate Bluetooth or mobile app for live result tracking
- Implement cloud database for long-term monitoring
- Use AI/ML to classify test results and health risk levels
- Add support for multiple sensor inputs (e.g., ammonia for kidney screening)


