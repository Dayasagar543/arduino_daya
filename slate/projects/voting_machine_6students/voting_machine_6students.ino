#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Set I2C address (0x27 or 0x3F)
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int NUM_CANDIDATES = 6;

// Pin assignments using ONLY digital pins (2 through 7)
const int switchPins[NUM_CANDIDATES] = {2, 3, 4, 5, 6, 7};
const int resetPin = 8; // Digital Pin 8 for Reset

// Vote counters
int votes[NUM_CANDIDATES] = {0, 0, 0, 0, 0, 0};

// State tracking for debouncing
bool lastState[NUM_CANDIDATES] = {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH};
bool lastStateReset = HIGH;

unsigned long lastDebounceTime[NUM_CANDIDATES] = {0, 0, 0, 0, 0, 0};
unsigned long lastDebounceTimeReset = 0;
const unsigned long debounceDelay = 50; // 50ms bounce protection

void setup() {
  lcd.init();
  lcd.backlight();

  // Configure switch pins with internal pull-ups
  for (int i = 0; i < NUM_CANDIDATES; i++) {
    pinMode(switchPins[i], INPUT_PULLUP);
  }
  pinMode(resetPin, INPUT_PULLUP);

  // Startup Message
  lcd.setCursor(0, 0);
  lcd.print("6-Way Voting System");
  lcd.setCursor(0, 1);
  lcd.print(" Digital Pins Only ");
  delay(2000);

  updateDisplay();
}

void loop() {
  unsigned long currentMillis = millis();

  // --- Read All 6 Candidate Switches ---
  for (int i = 0; i < NUM_CANDIDATES; i++) {
    bool reading = digitalRead(switchPins[i]);

    if (reading != lastState[i] && (currentMillis - lastDebounceTime[i]) > debounceDelay) {
      lastDebounceTime[i] = currentMillis;
      if (reading == LOW) { // Switch pressed (grounded)
        votes[i]++;
        updateDisplay();
      }
      lastState[i] = reading;
    }
  }

  // --- Read Reset Button ---
  bool readingReset = digitalRead(resetPin);
  if (readingReset != lastStateReset && (currentMillis - lastDebounceTimeReset) > debounceDelay) {
    lastDebounceTimeReset = currentMillis;
    if (readingReset == LOW) {
      for (int i = 0; i < NUM_CANDIDATES; i++) {
        votes[i] = 0;
      }
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("  Votes Reset!  ");
      delay(1000);
      updateDisplay();
    }
    lastStateReset = readingReset;
  }
}

// Function to update the 16x2 LCD display
void updateDisplay() {
  lcd.clear();
  
  // Top Line: C1, C2, C3
  lcd.setCursor(0, 0);
  lcd.print("1:"); lcd.print(votes[0]);
  lcd.setCursor(5, 0);
  lcd.print("2:"); lcd.print(votes[1]);
  lcd.setCursor(10, 0);
  lcd.print("3:"); lcd.print(votes[2]);

  // Bottom Line: C4, C5, C6
  lcd.setCursor(0, 1);
  lcd.print("4:"); lcd.print(votes[3]);
  lcd.setCursor(5, 1);
  lcd.print("5:"); lcd.print(votes[4]);
  lcd.setCursor(10, 1);
  lcd.print("6:"); lcd.print(votes[5]);
}