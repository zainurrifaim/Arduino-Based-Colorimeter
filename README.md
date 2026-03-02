# Arduino-Based Colorimeter

IoT RGB Colorimeter (LDR + LED)

A simple, cost-effective colorimeter built using an Arduino, an RGB LED, and a Light Dependent Resistor (LDR). This project is designed for both physical hardware implementation and Tinkercad simulation.

a. Objective

The primary goal of this project is to measure the Absorbance of liquid samples across three primary wavelengths (Red, Green, and Blue). By using the Beer-Lambert Law principle, this device quantifies how much light is absorbed by a solution, which can be used to determine the concentration of a substance or identify specific color characteristics in an IoT/educational context.

b. Specifications

Hardware Components

Microcontroller: Arduino Uno (or compatible)

Sensor: 3-Pin LDR Module (or discrete LDR with 10kΩ resistor)

Light Source: RGB LED (Common Cathode recommended)

Display: 16x2 I2C LCD (Address 0x27)

Controls: 2x Tactile Push Buttons

Resistors: * 3x 220Ω resistors (for LED protection)

1x 10kΩ resistor (only if using a 2-pin discrete LDR)

Wiring and Cabling

1. 3-Pin LDR Module

Most 3-pin LDR modules follow this pinout:

VCC: Connect to Arduino 5V

GND: Connect to Arduino GND

OUT (or S): Connect to Arduino A0

2. RGB LED (Common Cathode)

Common Pin (Longest): Connect to GND

Red Pin: Connect to Pin 2 (via 220Ω resistor)

Green Pin: Connect to Pin 3 (via 220Ω resistor)

Blue Pin: Connect to Pin 4 (via 220Ω resistor)

3. I2C LCD Display

GND: Connect to GND

VCC: Connect to 5V

SDA: Connect to A4 (on Uno)

SCL: Connect to A5 (on Uno)

4. Buttons

Button 1 (Blank): One side to Pin 8, other side to GND

Button 2 (Read): One side to Pin 9, other side to GND

c. Features

Multi-Spectrum Analysis: Measures absorbance for Red, Green, and Blue wavelengths individually.

Intelligent Calibration: A dedicated "Blank" mode to set the 100% transmission baseline using a reference solution (like clear water).

Signal Stability: Implements digital averaging (taking multiple samples per reading) to filter out sensor noise and electrical interference.

Dual-Platform Support: * Colorimeter_Final.ino: Optimized for 3-pin LDR modules (Physical hardware).

Colorimeter_Tinkercad.ino: Specifically adjusted for discrete 2-pin photoresistors used in simulations.

Real-time Feedback: LCD interface provides step-by-step instructions and immediate numerical results (0.00 to 2.00+ absorbance units).

Safety Guards: Includes software checks to prevent division-by-zero errors and prompts the user if calibration is skipped.

Mathematical Principle

The device calculates absorbance using the following formula:

$$A = \log_{10}\left(\frac{I_{blank}}{I_{sample}}\right)$$

(Note: In the physical LDR module setup, the ratio is inverted in code to account for the specific resistance-to-voltage curve of the pre-built module.)

Simulation Demo

You can test the logic and virtual circuit here:
(https://www.tinkercad.com/things/clHeNK5QqYa-colorimeter/editel?returnTo=https%3A%2F%2Fwww.tinkercad.com%2Fdashboard%2Fdesigns%2Fcircuits&sharecode=1dP5T396gbwIMmcHylbOa9vrMQ1EQgCTYE7Bpzo5IXw)

How to Use

Initialize: Power the Arduino and wait for the "Ready!" message.

Calibrate: Insert your "Blank" solution and press the button on Pin 8.

Measure: Replace the blank with your sample and press the button on Pin 9.

Analyze: Read the absorbance values (R, G, B) directly from the LCD or the Serial Monitor.