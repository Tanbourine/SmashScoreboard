#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define CS_PIN 10

LiquidCrystal_I2C lcd(0x27,20,4); //Set LCD I2C Address and initialize 20x4 screen
File myFile;

//INITIALIZE VARIABLES
char playerNames[256];

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Serial Comms Established!");

  
  //INITIALIZE LCD
  Serial.print("Initializing LCD...");
  lcd.begin();
  lcd.setBacklight(HIGH);
  lcd.home();
  lcd.print("Initializing LCD...");
  lcd.setCursor(0,1);
  lcd.print("...done!");
  delay(1000);
  lcd.clear();
  Serial.println("...done!");
 
  

  //INITIALIZE SD
  Serial.print("Initializing SD...");
  lcd.home();
  lcd.print("Initializing SD...");
  if(!SD.begin(CS_PIN)) {
    Serial.println("Initialize failed!");
    lcd.setCursor(0,1);
    lcd.print("Initialize failed!");
    return;
  }
  Serial.println("...done!");
  lcd.setCursor(0,1);
  lcd.print("...done!");
  delay(1000);
  lcd.clear();

  
  myFile = SD.open("names.txt", FILE_READ);
  if (myFile) {
    lcd.clear();
    Serial.print("Reading names.txt...");
    lcd.home();
    lcd.print("Reading...");
    lcd.setCursor(0,1);
    lcd.print("names.txt...");

    for (int i=0; i < myFile.size(); i++) {
      playerNames[i] = char(myFile.read());
    }
    
    myFile.close();

    Serial.println(playerNames);
  }

  else{
    Serial.println("error opening names.txt");
  }
 
  
}

void loop() {
  // put your main code here, to run repeatedly:

}
