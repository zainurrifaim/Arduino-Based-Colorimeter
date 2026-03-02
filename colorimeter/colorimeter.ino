/**
 * Final Colorimeter Sketch
 * * Description:
 * This code runs a simple colorimeter using an LDR, an RGB LED, and an I2C LCD.
 * It follows the Beer-Lambert law to calculate the absorbance of a sample.
 * * Features:
 * - Two-button operation: one for calibrating with a blank, one for measuring a sample.
 * - Averaging of sensor readings to reduce noise and improve accuracy.
 * - Clear user prompts on a 16x2 I2C LCD display.
 * - Robust button handling with debounce and single-press detection.
 * - Safe absorbance calculation with checks for calibration and division by zero.
 * * Hardware Setup:
 * - Arduino Uno (or similar)
 * - I2C LCD 16x2 (Address 0x27)
 * - Sensor: LDR on pin A0
 * - LEDs: Red on pin 2, Green on pin 3, Blue on pin 4
 * - Buttons: Blank/Calibrate on pin 8, Read/Measure on pin 9
 */

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <math.h> // For the log10() function

// Initialize the LCD display
LiquidCrystal_I2C lcd(0x27, 16, 2);

// --- Configuration Constants ---
const int numReadings = 10;      // Number of sensor readings to average for stability
const int sensorDelay = 10;      // Delay between individual readings (ms)
const int ledStabilizeTime = 50; // Time to wait for LED to reach full brightness

// --- Pin Definitions ---
const int sensorPin = A0;
const int ledRedPin = 2;
const int ledGreenPin = 3;
const int ledBluePin = 4;
const int buttonBlankPin = 8;
const int buttonReadPin = 9;

// --- Global Variables ---
double blankRed = 0, blankGreen = 0, blankBlue = 0;
double sampleRed = 0, sampleGreen = 0, sampleBlue = 0;
double absRed = 0, absGreen = 0, absBlue = 0;

// Flag to track whether calibration has been completed
bool isCalibrated = false;

void setup() {
  Serial.begin(9600);
  
  // Initialize the LCD and turn on the backlight
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Colorimeter");
  lcd.setCursor(0, 1);
  lcd.print("Initializing...");
  delay(2000);
  lcd.clear();

  // Set pin modes
  pinMode(ledRedPin, OUTPUT);
  pinMode(ledGreenPin, OUTPUT);
  pinMode(ledBluePin, OUTPUT);
  pinMode(sensorPin, INPUT);
  pinMode(buttonBlankPin, INPUT_PULLUP);
  pinMode(buttonReadPin, INPUT_PULLUP);
  
  Serial.println("Colorimeter Ready!");
  lcd.setCursor(0, 0);
  lcd.print("Ready!");
  lcd.setCursor(0, 1);
  lcd.print("Press Calibrate");
}

void loop() {
  // Check for Blank/Calibrate button press
  if (digitalRead(buttonBlankPin) == LOW) {
    delay(50); // Debounce delay
    calibrateBlank();
    // Wait for the button to be released to prevent re-triggering
    while(digitalRead(buttonBlankPin) == LOW);
  }
  
  // Check for Read/Measure button press
  if (digitalRead(buttonReadPin) == LOW) {
    delay(50); // Debounce delay
    measureSample();
    // Wait for the button to be released
    while(digitalRead(buttonReadPin) == LOW);
  }
}

// Function to handle blank calibration
void calibrateBlank() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Insert Blank...");
  lcd.setCursor(0, 1);
  lcd.print("Calibrating...");
  
  // Take readings for all three colors
  blankRed = averageLDR(ledRedPin);
  blankGreen = averageLDR(ledGreenPin);
  blankBlue = averageLDR(ledBluePin);
  
  isCalibrated = true; // Set the calibration flag
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Calibration OK!");
  Serial.println("Blank Calibration Done!");
  delay(1500);
  
  lcd.clear();
  lcd.print("Ready to Read");
}

// Function to measure sample absorbance
void measureSample() {
  // First, check if calibration has been performed
  if (!isCalibrated) {
    showError("Please Calibrate!");
    return;
  }
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Insert Sample...");
  lcd.setCursor(0, 1);
  lcd.print("Measuring...");
  
  // Take readings for the sample
  sampleRed = averageLDR(ledRedPin);
  sampleGreen = averageLDR(ledGreenPin);
  sampleBlue = averageLDR(ledBluePin);
  
  // Calculate absorbance for each color
  // Absorbance = log10(Sample / Blank)
  // LDR reading is higher for the sample (less light) and lower for the blank (more light).
  // This ensures the absorbance is a positive value.
  absRed   = (sampleRed > 0 && blankRed > 0) ? log10(sampleRed / blankRed) : 0;
  absGreen = (sampleGreen > 0 && blankGreen > 0) ? log10(sampleGreen / blankGreen) : 0;
  absBlue  = (sampleBlue > 0 && blankBlue > 0) ? log10(sampleBlue / blankBlue) : 0;
  
  displayResults();
}

// Function to average LDR readings for a specific LED
double averageLDR(int ledPin) {
  // Ensure all LEDs are off to prevent light interference
  digitalWrite(ledRedPin, LOW);
  digitalWrite(ledGreenPin, LOW);
  digitalWrite(ledBluePin, LOW);
  
  // Turn on the target LED and wait for it to stabilize
  digitalWrite(ledPin, HIGH);
  delay(ledStabilizeTime);
  
  long total = 0;
  for (int i = 0; i < numReadings; i++) {
    total += analogRead(sensorPin);
    delay(sensorDelay);
  }
  
  // Turn the LED off after reading
  digitalWrite(ledPin, LOW);
  
  // Return the average value
  return total / (double)numReadings;
}

// Function to display absorbance results on the LCD and Serial Monitor
void displayResults() {
  lcd.clear();
  
  // Display Red and Green absorbance on the first line
  lcd.setCursor(0, 0);
  lcd.print("R:");
  lcd.print(absRed, 2); // Print with 2 decimal places
  
  lcd.setCursor(8, 0);
  lcd.print("G:");
  lcd.print(absGreen, 2);
  
  // Display Blue absorbance on the second line
  lcd.setCursor(0, 1);
  lcd.print("B:");
  lcd.print(absBlue, 2);
  
  // Print results to Serial Monitor for logging
  Serial.println("Absorbance Readings:");
  Serial.print("R: "); Serial.println(absRed, 2);
  Serial.print("G: "); Serial.println(absGreen, 2);
  Serial.print("B: "); Serial.println(absBlue, 2);

  // The loop() function will wait for the button release, so no extra wait is needed here.
}

// Function to display a temporary error message
void showError(const char* message) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Error:");
  lcd.setCursor(0, 1);
  lcd.print(message);
  delay(2000);
  lcd.clear();
  lcd.print("Ready!");
}