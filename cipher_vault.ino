#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

// 1. Setup LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

// 2. Setup Keypad
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6}; 
byte colPins[COLS] = {5, 4, 3, 2}; 

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// 3. Pins & Variables
const int buzzerPin = 10;
const int greenLed = 11;
const int redLed = 12;

String generatedPass = "";
String inputPass = "";

void setup() {
  pinMode(buzzerPin, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(redLed, OUTPUT);
  
  lcd.init();
  lcd.backlight();
  
  randomSeed(analogRead(0)); 
  showIntro();
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    playKeyTone(); 
    
    if (key == 'A') {
      generateNewPass();
    } 
    else if (key == '#') {
      if (inputPass.length() > 0) checkPass();
    } 
    else if (key == '*') {
      inputPass = ""; 
      updateDisplay();
    } 
    else {
      if (inputPass.length() < 4) {
        inputPass += key;
        updateDisplay();
      }
    }
  }
}

void showIntro() {
  lcd.clear();
  lcd.print("PASS GENERATOR");
  lcd.setCursor(0, 1);
  lcd.print("Press 'A' to Start");
}

void generateNewPass() {
  generatedPass = "";
  for (int i = 0; i < 4; i++) {
    generatedPass += String(random(0, 10));
  }
  inputPass = "";
  lcd.clear();
  lcd.print("NEW PASS: ");
  lcd.print(generatedPass);
  lcd.setCursor(0, 1);
  lcd.print("TYPE: ");
  
  // Flash both LEDs briefly to show a reset
  digitalWrite(greenLed, HIGH);
  digitalWrite(redLed, HIGH);
  delay(100);
  digitalWrite(greenLed, LOW);
  digitalWrite(redLed, LOW);
}

void updateDisplay() {
  lcd.setCursor(6, 1);
  lcd.print("    "); 
  lcd.setCursor(6, 1);
  lcd.print(inputPass);
}

void checkPass() {
  lcd.clear();
  if (inputPass == generatedPass) {
    lcd.print(" ACCESS GRANTED ");
    lcd.setCursor(0,1);
    lcd.print("   CORRECT!!    ");
    
    digitalWrite(greenLed, HIGH); // Green ON
    tone(buzzerPin, 1500, 500);
    delay(2000);
    digitalWrite(greenLed, LOW);  // Green OFF
  } else {
    lcd.print(" ACCESS DENIED  ");
    lcd.setCursor(0,1);
    lcd.print(" WRONG PASSWORD ");
    
    digitalWrite(redLed, HIGH);   // Red ON
    tone(buzzerPin, 150, 1000);
    delay(2000);
    digitalWrite(redLed, LOW);    // Red OFF
  }
  
  lcd.clear();
  lcd.print("NEW PASS: ");
  lcd.print(generatedPass);
  lcd.setCursor(0, 1);
  lcd.print("TYPE: ");
  inputPass = "";
}

void playKeyTone() {
  tone(buzzerPin, 2000, 20); 
}