/**
 * Tinkercad Colorimeter Sketch
 * * Description:
 * This version is specifically adapted for Tinkercad using a discrete 2-pin 
 * photoresistor and a standard voltage divider circuit.
 * * * Tinkercad Hardware Setup:
 * - Arduino Uno
 * - I2C LCD 16x2 (Address 0x27)
 * - LEDs: Red on pin 2, Green on pin 3, Blue on pin 4
 * - Buttons: Blank/Calibrate on pin 8, Read/Measure on pin 9
 * - PHOTO SENSOR WIRING: 
 * - Photoresistor Leg 1: 5V
 * - Photoresistor Leg 2: A0 AND to a 10k Ohm Resistor
 * - 10k Ohm Resistor other leg: GND
 */

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <math.h> 

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int numReadings = 10;      
const int sensorDelay = 10;      
const int ledStabilizeTime = 50; 

const int sensorPin = A0;
const int ledRedPin = 2;
const int ledGreenPin = 3;
const int ledBluePin = 4;
const int buttonBlankPin = 8;
const int buttonReadPin = 9;

double blankRed = 0, blankGreen = 0, blankBlue = 0;
double sampleRed = 0, sampleGreen = 0, sampleBlue = 0;
double absRed = 0, absGreen = 0, absBlue = 0;

bool isCalibrated = false;

void setup() {
  Serial.begin(9600);
  
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Tinkercad Mode");
  lcd.setCursor(0, 1);
  lcd.print("Initializing...");
  delay(2000);
  lcd.clear();

  pinMode(ledRedPin, OUTPUT);
  pinMode(ledGreenPin, OUTPUT);
  pinMode(ledBluePin, OUTPUT);
  pinMode(sensorPin, INPUT);
  pinMode(buttonBlankPin, INPUT_PULLUP);
  pinMode(buttonReadPin, INPUT_PULLUP);
  
  Serial.println("Tinkercad Colorimeter Ready!");
  lcd.setCursor(0, 0);
  lcd.print("Ready!");
  lcd.setCursor(0, 1);
  lcd.print("Press Calibrate");
}

void loop() {
  if (digitalRead(buttonBlankPin) == LOW) {
    delay(50); 
    calibrateBlank();
    while(digitalRead(buttonBlankPin) == LOW);
  }
  
  if (digitalRead(buttonReadPin) == LOW) {
    delay(50); 
    measureSample();
    while(digitalRead(buttonReadPin) == LOW);
  }
}

void calibrateBlank() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Insert Blank...");
  lcd.setCursor(0, 1);
  lcd.print("Calibrating...");
  
  blankRed = averageLDR(ledRedPin);
  blankGreen = averageLDR(ledGreenPin);
  blankBlue = averageLDR(ledBluePin);
  
  isCalibrated = true; 
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Calibration OK!");
  Serial.println("Blank Calibration Done!");
  delay(1500);
  
  lcd.clear();
  lcd.print("Ready to Read");
}

void measureSample() {
  if (!isCalibrated) {
    showError("Please Calibrate!");
    return;
  }
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Insert Sample...");
  lcd.setCursor(0, 1);
  lcd.print("Measuring...");
  
  sampleRed = averageLDR(ledRedPin);
  sampleGreen = averageLDR(ledGreenPin);
  sampleBlue = averageLDR(ledBluePin);
  
  // TINKERCAD MATH ADJUSTMENT:
  // With the standard Tinkercad voltage divider (LDR to 5V, Resistor to GND),
  // more light = a higher analog value. 
  // Therefore, Blank (high light) > Sample (low light).
  // Absorbance = log10(Blank / Sample)
  absRed   = (sampleRed > 0 && blankRed > 0) ? log10(blankRed / sampleRed) : 0;
  absGreen = (sampleGreen > 0 && blankGreen > 0) ? log10(blankGreen / sampleGreen) : 0;
  absBlue  = (sampleBlue > 0 && blankBlue > 0) ? log10(blankBlue / sampleBlue) : 0;
  
  displayResults();
}

double averageLDR(int ledPin) {
  digitalWrite(ledRedPin, LOW);
  digitalWrite(ledGreenPin, LOW);
  digitalWrite(ledBluePin, LOW);
  
  digitalWrite(ledPin, HIGH);
  delay(ledStabilizeTime);
  
  long total = 0;
  for (int i = 0; i < numReadings; i++) {
    total += analogRead(sensorPin);
    delay(sensorDelay);
  }
  
  digitalWrite(ledPin, LOW);
  return total / (double)numReadings;
}

void displayResults() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("R:");
  lcd.print(absRed, 2); 
  
  lcd.setCursor(8, 0);
  lcd.print("G:");
  lcd.print(absGreen, 2);
  
  lcd.setCursor(0, 1);
  lcd.print("B:");
  lcd.print(absBlue, 2);
  
  Serial.println("Absorbance Readings:");
  Serial.print("R: "); Serial.println(absRed, 2);
  Serial.print("G: "); Serial.println(absGreen, 2);
  Serial.print("B: "); Serial.println(absBlue, 2);
}

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