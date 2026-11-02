#include <Servo.h>

// Pin Definitions
const int BUTTON_PIN = 2;    // Pushbutton pin (uses internal pull-up)
const int VEHICLE_RED = 11;  // Vehicle traffic lights
const int VEHICLE_YELLOW = 10;
const int VEHICLE_GREEN = 9;
const int SERVO_PIN = 6;  // Servo motor signal pin
int buzzer_pin = 7;

// Servo Object
Servo barricadeServo;

// Timing Variables (in milliseconds)
const unsigned long YELLOW_DELAY = 2000;  // 2 seconds for yellow light
const unsigned long CROSS_TIME = 7000;    // 7 seconds for pedestrians to cross
const unsigned long RESET_DELAY = 2000;   // 2 seconds buffer during transition
const unsigned long buzzer_DELAY = 200;   // 2 seconds buffer during transition

// Servo Positions
const int BARRICADE_OPEN = 90;     // Vehicles can pass
const int BARRICADE_CLOSED = 0;  // Barricade down, vehicles stopped

void setup() {
  // Initialize LED Pins as Outputs
  pinMode(VEHICLE_RED, OUTPUT);
  pinMode(VEHICLE_YELLOW, OUTPUT);
  pinMode(VEHICLE_GREEN, OUTPUT);
  pinMode(buzzer_pin, OUTPUT);

  // Initialize Button Pin with Internal Pull-up Resistor
  // Active LOW: Button reads LOW when pressed, HIGH when idle
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  // Attach Servo
  barricadeServo.attach(SERVO_PIN);

  // Set Initial State (Safe for Vehicles)
  setNormalTrafficState();
}

void loop() {
  // Check if the button is pressed (LOW due to INPUT_PULLUP)
  if (digitalRead(BUTTON_PIN) == LOW) {
    triggerPedestrianSequence();
  }
}

// Sets the default state where vehicles move and pedestrians wait
void setNormalTrafficState() {
  barricadeServo.write(BARRICADE_OPEN);
  digitalWrite(VEHICLE_GREEN, HIGH);
  digitalWrite(VEHICLE_YELLOW, LOW);
  digitalWrite(VEHICLE_RED, LOW);
}

// Handles the smart traffic transition logic
void triggerPedestrianSequence() {
  // 1. Warn vehicles (Green -> Yellow)
  digitalWrite(VEHICLE_GREEN, LOW);
  digitalWrite(VEHICLE_YELLOW, HIGH);
  delay(YELLOW_DELAY);

  // 2. Stop vehicles (Yellow -> Red)
  digitalWrite(VEHICLE_YELLOW, LOW);
  digitalWrite(VEHICLE_RED, HIGH);
  delay(500);  // Short safety pause before barricade drops

  // 3. Drop the barricade to physically block vehicles
  barricadeServo.write(BARRICADE_CLOSED);
  delay(1000);  // Allow time for the servo to move
  for (int i = 0; i < 14; i++) {
    buzzer();
  }
  // Hold the crossing state for the designated time
  delay(CROSS_TIME);

  delay(RESET_DELAY);  // Safety buffer before lifting barricade

  // 6. Lift barricade and return vehicle light to Green
  barricadeServo.write(BARRICADE_OPEN);
  delay(1000);  // Allow time for the servo to lift
  digitalWrite(VEHICLE_RED, LOW);
  digitalWrite(VEHICLE_GREEN, HIGH);

  // Anti-spam delay so pedestrians can't immediately trigger it again
  delay(3000);
}

void buzzer() {
  digitalWrite(buzzer_pin, HIGH);
  delay(buzzer_DELAY);
  digitalWrite(buzzer_pin, LOW);
  delay(buzzer_DELAY);
}