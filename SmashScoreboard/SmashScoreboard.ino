#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4); //Set LCD I2C Address and initialize 20x4 screen

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  lcd.begin();
  lcd.setBacklight(HIGH);
  lcd.home();
  lcd.print("Hello there");
  lcd.setCursor(0,1);
  lcd.print("Darren");
  
}

void loop() {
  // put your main code here, to run repeatedly:

}
