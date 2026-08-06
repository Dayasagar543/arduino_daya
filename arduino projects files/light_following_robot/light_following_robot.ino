#include <AFMotor.h>

// Pins for Light Dependent Resistors
const int left_ldr = A0;
const int right_ldr = A1;
const int center_ldr = A2;

// Create motor objects for differential drive
AF_DCMotor motor1(1); // Usually Left Motor
AF_DCMotor motor2(2); // Usually Right Motor

void setup() {
  Serial.begin(9600);
  
  // Set initial speeds
  motor1.setSpeed(150);
  motor2.setSpeed(150);

  // Ensure motors are stopped initially
  motor1.run(RELEASE);
  motor2.run(RELEASE);
}

void loop() {
  // 1. Read all sensors instantly without massive delays
  int left_ldr_data = analogRead(left_ldr);
  int right_ldr_data = analogRead(right_ldr);
  int center_ldr_data = analogRead(center_ldr);

  // Debugging outputs (Printing all at once)
  Serial.print("L: "); Serial.print(left_ldr_data);
  Serial.print(" | C: "); Serial.print(center_ldr_data);
  Serial.print(" | R: "); Serial.println(right_ldr_data);

  // 2. Control Logic (Most specific conditions must go first!)
  
  // Condition A: All sensors detect light (or darkness) -> Move Forward smoothly
  if (center_ldr_data <= 30 && left_ldr_data <= 30 && right_ldr_data <= 30) {
    motor1.run(FORWARD);
    motor2.run(FORWARD);
    motor1.setSpeed(150);
    motor2.setSpeed(150);
  }
  // Condition B: Center and Left are triggered -> Turn Left
  else if (center_ldr_data < 50 && left_ldr_data < 30) {
    motor1.run(BACKWARD); // Pivot left motor backward
    motor2.run(FORWARD);  // Pivot right motor forward
    motor1.setSpeed(120);
    delay()
    motor2.setSpeed(150);
  } 
  // Condition C: Center and Right are triggered -> Turn Right
  else if (center_ldr_data < 50 && right_ldr_data < 30) {
    motor1.run(FORWARD);  // Pivot left motor forward
    motor2.run(BACKWARD); // Pivot right motor backward
    motor1.setSpeed(150);
    motor2.setSpeed(120);
  } 
  // Condition D: Just center is triggered -> Straight ahead
  else if (center_ldr_data < 50) {
    motor1.run(FORWARD);
    motor2.run(FORWARD);
    motor1.setSpeed(150);
    motor2.setSpeed(150);
  } 
  // Condition E: No conditions met -> Stop safely
  else {
    motor1.run(RELEASE);
    motor2.run(RELEASE);
  }

  delay(50); // Small pause (50ms) just to give the processor a tiny breather
}