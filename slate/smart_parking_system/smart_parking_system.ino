
#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// RFID pins
#define SS_PIN 10
#define RST_PIN 9

// Other component pins
#define SERVO_PIN 6
#define IR_PIN 2

// LCD address: commonly 0x27 or 0x3F
LiquidCrystal_I2C lcd(0x27, 16, 2);

MFRC522 rfid(SS_PIN, RST_PIN);
Servo gateServo;

// Replace this with your own RFID card UID
byte authorizedUID[] = {0xDE, 0xAD, 0xBE, 0xEF};
const byte UID_LENGTH = sizeof(authorizedUID);

const int GATE_CLOSED = 0;
const int GATE_OPEN = 90;

// Most IR modules output LOW when an object is detected.
// Change to HIGH if your sensor works the opposite way.
const int IR_DETECTED = LOW;

bool gateIsOpen = false;
unsigned long gateOpenedAt = 0;
const unsigned long GATE_TIMEOUT = 5000;

bool cardMatches() {
  if (rfid.uid.size != UID_LENGTH) {
    return false;
  }

  for (byte i = 0; i < UID_LENGTH; i++) {
    if (rfid.uid.uidByte[i] != authorizedUID[i]) {
      return false;
    }
  }

  return true;
}

void printUID() {
  Serial.print("Card UID: ");

  for (byte i = 0; i < rfid.uid.size; i++) {
    if (rfid.uid.uidByte[i] < 0x10) {
      Serial.print("0");
    }

    Serial.print(rfid.uid.uidByte[i], HEX);

    if (i < rfid.uid.size - 1) {
      Serial.print(" ");
    }
  }

  Serial.println();
}

void showReady() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Smart Parking");
  lcd.setCursor(0, 1);
  lcd.print("Scan RFID Card");
}

void openGate() {
  gateServo.write(GATE_OPEN);
  gateIsOpen = true;
  gateOpenedAt = millis();

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Access Granted");
  lcd.setCursor(0, 1);
  lcd.print("Gate Open");
}

void setup() {
  Serial.begin(9600);

  pinMode(IR_PIN, INPUT);

  SPI.begin();
  rfid.PCD_Init();

  gateServo.attach(SERVO_PIN);
  gateServo.write(GATE_CLOSED);

  lcd.init();
  lcd.backlight();

  showReady();

  Serial.println("Smart Parking System Ready");
  Serial.println("Scan your RFID card.");
}

void loop() {
  // Keep the gate open while the vehicle is detected.
  bool vehicleDetected = (digitalRead(IR_PIN) == IR_DETECTED);

  if (gateIsOpen) {
    if (!vehicleDetected &&
        millis() - gateOpenedAt >= GATE_TIMEOUT) {

      gateServo.write(GATE_CLOSED);
      gateIsOpen = false;

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Gate Closed");
      delay(1000);

      showReady();
    }

    return;
  }

  // Wait for a new RFID card
  if (!rfid.PICC_IsNewCardPresent()) {
    return;
  }

  if (!rfid.PICC_ReadCardSerial()) {
    return;
  }

  printUID();

  if (cardMatches()) {
    openGate();
  } else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Access Denied");
    lcd.setCursor(0, 1);
    lcd.print("Invalid RFID");

    Serial.println("Unauthorized card");

    delay(1500);
    showReady();
  }

  // Stop communication with the current RFID card
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}
