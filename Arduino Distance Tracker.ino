#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int hallsensor = 6;
unsigned int counter = 0;
bool flag = false;
const float wheelCircumferenceMeter = 0.5; // Value to calculate the wheel circumference (in meters)

void setup() {
  pinMode(hallsensor, INPUT); // Set Hall sensor pin as INPUT
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("System Starting"); // Display "System Starting" at the beginning
  delay(2000); // Wait for 2 seconds
  lcd.clear(); // Clear the screen, then display km and meters
  lcd.setCursor(0, 0);
}

void loop() {
  int sensorStatus = digitalRead(hallsensor);

  if (sensorStatus == LOW && !flag) {
    counter++; // Increase the counter when the sensor detects a magnet passing by, regardless of the speed
    flag = true; // Set the flag to true to prepare for the next passage
  }

  if (sensorStatus == HIGH) {
    flag = false; // If the sensor status changes, set the flag to false to prepare for the next passage
  }

  float distanceMeter = counter * wheelCircumferenceMeter;
  float distanceKilometer = distanceMeter / 1000.0; // Convert distance to kilometers by dividing by 1000

  lcd.setCursor(0, 0); 
  lcd.print(distanceKilometer, 2);
  lcd.setCursor(5, 0); 
  lcd.print("KM");

  lcd.setCursor(9, 0); 
  lcd.print(distanceMeter, 2); 
  lcd.setCursor(15, 0);
  lcd.print("M"); 
}
