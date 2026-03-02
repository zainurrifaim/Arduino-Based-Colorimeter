# 🎨 Arduino-Based Colorimeter

> **IoT RGB Colorimeter (LDR + LED)** — A cost-effective, educational light absorption measurement system

A simple yet powerful colorimeter built using an Arduino, an RGB LED, and a Light Dependent Resistor (LDR). This project supports both **physical hardware implementation** and **Tinkercad simulation**, making it perfect for learning and prototyping.

---

## 📑 Contents

- [Objective](#-objective)
- [Specifications](#-specifications)
- [Features](#-features)
- [Mathematical Principle](#-mathematical-principle)
- [Try It Out](#-try-it-out)
- [How to Use](#-how-to-use)
- [Project Structure](#-project-structure)

---

## 📋 Objective

Measure the **absorbance of liquid samples** across three primary wavelengths (Red, Green, and Blue) using the **Beer-Lambert Law principle**. This device quantifies how much light is absorbed by a solution, enabling:

- Determination of substance concentration
- Color characteristic analysis  
- Educational IoT demonstrations

---

## 🔧 Specifications

### Hardware Components

| Component | Description |
|-----------|-------------|
| **Microcontroller** | Arduino Uno (or compatible) |
| **Sensor** | 3-Pin LDR Module (or discrete LDR with 10kΩ resistor) |
| **Light Source** | RGB LED (Common Cathode recommended) |
| **Display** | 16×2 I2C LCD (Address 0x27) |
| **Controls** | 2× Tactile Push Buttons |
| **Resistors** | 3× 220Ω (LED protection) + 1× 10kΩ (optional, for discrete LDR) |

### Wiring and Pinout

#### 1️⃣ 3-Pin LDR Module

| Module Pin | Arduino Connection |
|------------|-------------------|
| **VCC** | 5V |
| **GND** | GND |
| **OUT (or S)** | A0 |

#### 2️⃣ RGB LED (Common Cathode)

| LED Pin | Arduino Connection | Details |
|---------|-------------------|---------|
| **Common (Longest)** | GND | — |
| **Red Pin** | Pin 2 | via 220Ω resistor |
| **Green Pin** | Pin 3 | via 220Ω resistor |
| **Blue Pin** | Pin 4 | via 220Ω resistor |

#### 3️⃣ I2C LCD Display

| LCD Pin | Arduino Connection |
|---------|-------------------|
| **GND** | GND |
| **VCC** | 5V |
| **SDA** | A4 |
| **SCL** | A5 |

#### 4️⃣ Control Buttons

| Button | Arduino Pin | Other Connection |
|--------|------------|------------------|
| **Blank** | Pin 8 | GND |
| **Read** | Pin 9 | GND |

---

## ✨ Features

- **🌈 Multi-Spectrum Analysis** — Measures absorbance for Red, Green, and Blue wavelengths individually

- **⚙️ Intelligent Calibration** — Dedicated "Blank" mode to set 100% transmission baseline using a reference solution

- **📊 Signal Stability** — Digital averaging (multiple samples per reading) to filter sensor noise and electrical interference

- **🔄 Dual-Platform Support**
  - `colorimeter.ino` — Optimized for 3-pin LDR modules (Physical hardware)
  - `colorimeter_tinkercad.ino` — Adjusted for discrete 2-pin photoresistors (Tinkercad simulations)

- **💻 Real-time Feedback** — LCD interface with step-by-step instructions and instant numerical results (0.00 to 2.00+ absorbance units)

- **🛡️ Safety Guards** — Software checks prevent division-by-zero errors and prompt if calibration is skipped

---

## 📐 Mathematical Principle

The device calculates absorbance using the **Beer-Lambert Law**:

$$A = \log_{10}\left(\frac{I_{blank}}{I_{sample}}\right)$$

> **Note:** In the physical LDR module setup, the ratio is inverted in code to account for the specific resistance-to-voltage curve of the pre-built module.

---

## 🧪 Try It Out

**[View Interactive Tinkercad Simulation](https://www.tinkercad.com/things/clHeNK5QqYa-colorimeter/editel?returnTo=https%3A%2F%2Fwww.tinkercad.com%2Fdashboard%2Fdesigns%2Fcircuits&sharecode=1dP5T396gbwIMmcHylbOa9vrMQ1EQgCTYE7Bpzo5IXw)**

Test the logic and virtual circuit without building physical hardware!

---

## 🚀 How to Use

| Step | Action | Details |
|------|--------|---------|
| **1️⃣ Initialize** | Power the Arduino | Wait for "Ready!" message on LCD |
| **2️⃣ Calibrate** | Insert blank solution + press Pin 8 button | Sets 100% transmission baseline (use clear water) |
| **3️⃣ Measure** | Replace with sample + press Pin 9 button | Measures actual sample absorbance |
| **4️⃣ Analyze** | Read the results | LCD or Serial Monitor displays R, G, B absorbance values |

---

## 📂 Project Structure

```
Arduino-Based Colorimeter/
├── colorimeter/
│   └── colorimeter.ino           # Physical hardware version (3-pin LDR)
├── tinkercad_simulation/
│   └── colorimeter_tinkercad.ino # Simulation version (discrete photoresistor)
├── CAD/                          # 3D models and hardware designs
└── README.md                     # This file
```

---

## 💡 Tips & Troubleshooting

- **Calibration is Key** — Accurate blank readings directly impact measurement accuracy
- **Stable Environment** — Keep ambient light constant during measurements
- **Averaging** — The firmware automatically averages multiple readings to reduce noise
- **Serial Monitor** — Open the Serial Monitor (9600 baud) for detailed debugging info

---

## 📚 References

- **Beer-Lambert Law** — Fundamental principle for absorbance measurement
- **Arduino Documentation** — [arduino.cc](https://www.arduino.cc)
- **I2C LCD Displays** — Standard address 0x27 for 16×2 displays
- **Tinkercad** — [tinkercad.com](https://www.tinkercad.com) for circuit simulation

---

## ⭐ Perfect For

✓ Physics & Chemistry Education  
✓ IoT Projects & Prototyping  
✓ Sensor Integration Learning  
✓ Arduino Skill Development  
✓ DIY Analytical Instruments  

---
