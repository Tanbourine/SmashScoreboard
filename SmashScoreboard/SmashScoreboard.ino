#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define P1_PIN 2
#define P2_PIN 3
#define CS_PIN 10


LiquidCrystal_I2C lcd(0x27, 20, 4); //Set LCD I2C Address and initialize 20x4 screen
File myFile;

//INITIALIZE VARIABLES
char playerNames[50];
char charNames[157];

int P1_location = 1;
int P2_location = 1;

//INITIALIZE PINS
int P1_BUTTON = 0;
int P2_BUTTON = 0;


void setup() {

  //SETUP PINS
  pinMode(P1_PIN, INPUT);
  pinMode(P2_PIN, INPUT);


  //INITIALIZE SERIAL
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println(F("Serial Comms Established!"));


  //INITIALIZE LCD
  Serial.print(F("Initializing LCD..."));
  lcd.begin();
  lcd.setBacklight(HIGH);
  lcd.clear();
  Serial.println(F("...done!"));



  //INITIALIZE SD
  Serial.print(F("Initializing SD..."));
  if (!SD.begin(CS_PIN)) {
    Serial.println(F("Initialize failed!"));
    return;
  }
  Serial.println(F("...done!"));

  //PLAYER NAMES SD TO ARDUINO
  myFile = SD.open("names.txt", FILE_READ);
  if (myFile) {
    Serial.print(F("Reading names.txt..."));

    for (int i = 0; i < myFile.size(); i++) {
      playerNames[i] = char(myFile.read());
    }

    myFile.close();
    Serial.println(F("...done!"));
    //Serial.println(playerNames);
  }
  else {
    Serial.println(F("error opening names.txt"));
  }


  //CHARACTER NAMES SD TO ARDUINO
  myFile = SD.open("chars.txt", FILE_READ);
  if (myFile) {
    Serial.print(F("Reading chars.txt..."));

    for (int i = 0; i < myFile.size(); i++) {
      charNames[i] = char(myFile.read());
    }

    myFile.close();
    Serial.println(F("...done!"));
    //Serial.println(charNames);
  }

  else {
    Serial.println(F("error opening names.txt"));
  }


  //MAIN DEFAULT SCREEN
  lcd.clear();
  lcd.home();
  lcd.print(F("PLAYER 1    PLAYER 2"));
  lcd.setCursor(0, 2);
  lcd.print(F("CHAR     VS     CHAR"));
  lcd.setCursor(0, 3);
  lcd.print(F("WINS= 000  000 =WINS"));
}


int cycleP1(int location) {
  char P1[6];
  int counter = 0;
  
  for (int i = 0; i<6;i++) {
    P1[i] = ' ';
  }
  
  for (int i = location; i <= 50; i++) {
    if (playerNames[i] != ',') {
      P1[counter] = playerNames[i];
      counter++;
    }
    else {
      location = i + 1;
      break;
    }
  }
  
  if (location > 36) {
    location = 1;
  }
  lcd.home();
  lcd.print("          ");
  lcd.home();
  lcd.print(P1);
  Serial.println(P1);
  return location;
}


int cycleP2(int location) {
  char P2[6];
  int counter = 0;
  
  for (int i = 0; i<6;i++) {
    P2[i] = ' ';
  }
  
  for (int i = location; i <= 50; i++) {
    if (playerNames[i] != ',') {
      P2[counter] = playerNames[i];
      counter++;
    }
    else {
      location = i + 1;
      break;
    }
  }
  
  if (location > 36) {
    location = 1;
  }

  
  lcd.setCursor(12,0);
  lcd.print("       ");
  lcd.setCursor(20-counter,0);
  lcd.print(P2);
  Serial.println(P2);
  return location;
}


void loop() {
  // put your main code here, to run repeatedly:
  P1_BUTTON = digitalRead(P1_PIN);
  P2_BUTTON = digitalRead(P2_PIN);
  
  if (P1_BUTTON == HIGH) {
    P1_location = cycleP1(P1_location);
  }

  if (P2_BUTTON == HIGH) {
    P2_location = cycleP2(P2_location);
  }

  

  delay(250);

}
