#include <AFMotor.h>

// Sensor Pin Definitions (3 groups of 3 parallel LDRs)
const int left_side   = A0;
const int center      = A1;
const int right_side  = A2;

// Motor Definitions (Adafruit Motor Shield M1 and M2)
AF_DCMotor Motor1(1, MOTOR12_1KHZ); 
AF_DCMotor Motor2(2, MOTOR12_1KHZ); 

// Tuning Configuration for Light Avoidance
const int threshold = 40;  // Minimum difference in light intensity to trigger a turn
const int baseSpeed = 140; // Cruising motor speed (0-255)
const int turnSpeed = 160; // Sharp turning motor speed (0-255)

void setup() {
  // Analog pins are INPUT by default, but keeping your explicit initialization style
  pinMode(left_side, INPUT);
  pinMode(center, INPUT);
  pinMode(right_side, INPUT);
  
  Serial.begin(9600); // Added for calibration tracking
  forward(); 
}

void loop() {
  // Read current light levels from each zone (0 to 1023)
  int ls = analogRead(left_side);
  int cs = analogRead(center);
  int rs = analogRead(right_side);

  // --- LIGHT AVOIDER LOGIC MATRIX ---
  // Note: This logic assumes HIGHER value = MORE LIGHT (standard pull-down LDR wiring)
  
  // Case 1: Strong light directly in front -> Back up and turn Left away from it
  if (cs > ls && cs > rs && cs > 400) {
    reverse_and_turn("left");
  } 
  // Case 2: Light is stronger on the Left -> Turn Right to avoid it
  else if (ls > rs && (ls - rs) > threshold) {
    right();
  } 
  // Case 3: Light is stronger on the Right -> Turn Left to avoid it
  else if (rs > ls && (rs - ls) > threshold) {
    left();
  } 
  // Case 4: Balanced lighting or ambient shadows -> Move Forward safely
  else {
    forward();
  }

  delay(30); // Short stability pause
}

// Escape maneuver helper function (adapted from your format)
void reverse_and_turn(String direction) {
  reverse();
  delay(600); // Back up safely away from the light source
  if (direction == "left") {
    left();
  } else {
    right();
  }
  delay(500); // Duration of the escape pivot turn
}

// MOTOR CONTROL FUNCTIONS (Integrated with your speed configurations)

void forward() {
  Motor1.run(FORWARD);
  Motor2.run(FORWARD);
  Motor1.setSpeed(baseSpeed);
  Motor2.setSpeed(baseSpeed);
}

void reverse() {
  Motor1.run(BACKWARD);
  Motor2.run(BACKWARD);
  Motor1.setSpeed(baseSpeed);
  Motor2.setSpeed(baseSpeed);
}

void right() {
  Motor1.run(FORWARD);
  Motor2.run(BACKWARD);
  Motor1.setSpeed(turnSpeed);
  Motor2.setSpeed(turnSpeed);
}

void left() {
  Motor1.run(BACKWARD);
  Motor2.run(FORWARD);
  Motor1.setSpeed(turnSpeed);
  Motor2.setSpeed(turnSpeed);
}

void stp() {
  Motor1.run(RELEASE);
  Motor2.run(RELEASE);
  Motor1.setSpeed(0);
  Motor2.setSpeed(0);
}
