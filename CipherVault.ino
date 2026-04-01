// CipherVault - Arduino Random Password Generator & Verification System
// Hardware: Arduino Uno, 16x2 I2C LCD, 4x4 Matrix Keypad, Green/Red LEDs, Passive Buzzer

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

// --- Pin Definitions ---
#define BUZZER_PIN        10
#define GREEN_LED         11
#define RED_LED           12

// --- Constants ---
#define PASSWORD_LENGTH      4
#define RESULT_DISPLAY_MS 3000

// --- LCD Setup ---
// I2C address 0x27 is common; change to 0x3F if the display is blank
LiquidCrystal_I2C lcd(0x27, 16, 2);

// --- Keypad Setup ---
const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// --- State Variables ---
String generatedPassword = "";
String enteredPassword   = "";
bool   passwordReady     = false;

// ---------------------------------------------------------------------------
// Setup
// ---------------------------------------------------------------------------
void setup() {
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED,   OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  digitalWrite(GREEN_LED, LOW);
  digitalWrite(RED_LED,   LOW);

  // Seed the RNG from an unconnected analog pin for better randomness
  randomSeed(analogRead(A0));

  lcd.init();
  lcd.backlight();

  showWelcome();
}

// ---------------------------------------------------------------------------
// Main Loop
// ---------------------------------------------------------------------------
void loop() {
  char key = keypad.getKey();

  if (key == NO_KEY) return;

  if (key == 'A') {
    // Generate a new random 4-digit password
    generatePassword();
  } else if (key == '*') {
    // Clear the current entry
    clearEntry();
  } else if (key == '#') {
    // Submit and verify
    if (passwordReady) {
      verifyPassword();
    }
  } else if (key >= '0' && key <= '9') {
    // Numeric input – accept up to PASSWORD_LENGTH digits
    if (passwordReady && enteredPassword.length() < PASSWORD_LENGTH) {
      enteredPassword += key;
      updateEntryDisplay();
    }
  }
}

// ---------------------------------------------------------------------------
// Helper Functions
// ---------------------------------------------------------------------------

void showWelcome() {
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("CipherVault");
  lcd.setCursor(1, 1);
  lcd.print("Press A to Start");
}

void generatePassword() {
  // Build a random PASSWORD_LENGTH-digit string (leading zeros allowed)
  generatedPassword = "";
  for (int i = 0; i < PASSWORD_LENGTH; i++) {
    generatedPassword += String(random(0, 10));
  }

  enteredPassword = "";
  passwordReady   = true;

  // Show the generated password on the top row
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Code: ");
  lcd.print(generatedPassword);

  // Prompt for entry on the bottom row
  lcd.setCursor(0, 1);
  lcd.print("Enter: ");
}

void clearEntryField() {
  lcd.setCursor(7, 1);
  for (int i = 0; i < PASSWORD_LENGTH; i++) lcd.print(' ');
  lcd.setCursor(7, 1);
}

void clearEntry() {
  if (!passwordReady) return;

  enteredPassword = "";
  clearEntryField();
}

void updateEntryDisplay() {
  clearEntryField();
  lcd.print(enteredPassword);
}

void verifyPassword() {
  if (enteredPassword == generatedPassword) {
    accessGranted();
  } else {
    accessDenied();
  }

  // Wait a moment then return to the welcome screen
  delay(RESULT_DISPLAY_MS);
  passwordReady   = false;
  generatedPassword = "";
  enteredPassword   = "";
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(RED_LED,   LOW);
  showWelcome();
}

void accessGranted() {
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("ACCESS GRANTED");
  lcd.setCursor(3, 1);
  lcd.print("Welcome! :)");

  digitalWrite(GREEN_LED, HIGH);

  // Play a short ascending "success" melody
  tone(BUZZER_PIN, 523, 150);  // C5
  delay(170);
  tone(BUZZER_PIN, 659, 150);  // E5
  delay(170);
  tone(BUZZER_PIN, 784, 150);  // G5
  delay(170);
  tone(BUZZER_PIN, 1047, 300); // C6
  delay(320);
  noTone(BUZZER_PIN);
}

void accessDenied() {
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("ACCESS DENIED");
  lcd.setCursor(2, 1);
  lcd.print("Try Again :(");

  digitalWrite(RED_LED, HIGH);

  // Play a low-pitched "error" tone
  tone(BUZZER_PIN, 200, 500);
  delay(520);
  tone(BUZZER_PIN, 150, 700);
  delay(720);
  noTone(BUZZER_PIN);
}
