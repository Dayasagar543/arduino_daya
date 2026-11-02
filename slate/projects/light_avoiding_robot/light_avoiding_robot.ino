#include <AFMotor.h>  // Include the Adafruit Motor Shield V1 library

// --- SENSOR PIN DEFINITIONS ---
// The shield leaves analog pins A0 to A5 entirely open for sensor inputs.
const int leftZonePin   = A0; 
const int centerZonePin = A1; 
const int rightZonePin  = A2; 

// --- MOTOR CONFIGURATION ---
// Connect your 2 DC motors to terminals M1 and M2 on the L293D shield
AF_DCMotor motorLeft(1);  // Left Motor on terminal M1
AF_DCMotor motorRight(2); // Right Motor on terminal M2

// --- TUNING CONFIGURATION ---
const int threshold = 40;  // Sensitivity: Min difference in light to trigger a turn
const int baseSpeed = 150; // Normal cruising speed (0 to 255)
const int turnSpeed = 180; // Speed during sharp pivot turns (0 to 255)

void setup() {
  // Start Serial Monitor for debugging sensor readings
  Serial.begin(9600);
  Serial.println("Light Avoider Robot Initialized!");

  // Initialize motor states
  motorLeft.setSpeed(baseSpeed);
  motorRight.setSpeed(baseSpeed);
  
  motorLeft.run(RELEASE);  // Stop motors initially
  motorRight.run(RELEASE);
}

void loop() {
  // Read current light values from each sensor zone
  int lightLeft   = analogRead(leftZonePin);
  int lightCenter = analogRead(centerZonePin);
  int lightRight  = analogRead(rightZonePin);

  // Print values to the Serial Monitor to help you calibrate
  Serial.print("Left: ");   Serial.print(lightLeft);
  Serial.print(" | Center: "); Serial.print(lightCenter);
  Serial.print(" | Right: ");  Serial.println(lightRight);

  // --- LIGHT AVOIDING LOGIC ---
  // (Assumes a HIGHER analog value means MORE light. 
  // If your specific LDR setup reads lower values in bright light, reverse the '>' symbols to '<')

  // Scenario 1: Bright light detected directly in front -> Backup and pivot away
  if (lightCenter > lightLeft && lightCenter > lightRight && lightCenter > 400) {
    moveBackward();
    delay(500); 
    turnRight(); 
    delay(400);
  }
  // Scenario 2: Stronger light on the Left -> Turn Right to avoid it
  else if (lightLeft > lightRight && (lightLeft - lightRight) > threshold) {
    turnRight();
  }
  // Scenario 3: Stronger light on the Right -> Turn Left to avoid it
  else if (lightRight > lightLeft && (lightRight - lightLeft) > threshold) {
    turnLeft();
  }
  // Scenario 4: Shadows/even lighting -> Drive straight forward into the darker path
  else {
    moveForward();
  }

  delay(40); // Small pause for loop processing stability
}

// --- MOVEMENT HELPER FUNCTIONS ---

void moveForward() {
  motorLeft.setSpeed(baseSpeed);
  motorRight.setSpeed(baseSpeed);
  motorLeft.run(FORWARD);
  motorRight.run(FORWARD);
}

void moveBackward() {
  motorLeft.setSpeed(baseSpeed);
  motorRight.setSpeed(baseSpeed);
  motorLeft.run(BACKWARD);
  motorRight.run(BACKWARD);
}

void turnLeft() {
  motorLeft.setSpeed(turnSpeed);
  motorRight.setSpeed(turnSpeed);
  // Left wheel moves backward, right wheel moves forward to pivot sharply away from light
  motorLeft.run(BACKWARD);
  motorRight.run(FORWARD);
}

void turnRight() {
  motorLeft.setSpeed(turnSpeed);
  motorRight.setSpeed(turnSpeed);
  // Right wheel moves backward, left wheel moves forward to pivot sharply away from light
  motorLeft.run(FORWARD);
  motorRight.run(BACKWARD);
}

void stopRobot() {
  motorLeft.run(RELEASE);
  motorRight.run(RELEASE);
}
