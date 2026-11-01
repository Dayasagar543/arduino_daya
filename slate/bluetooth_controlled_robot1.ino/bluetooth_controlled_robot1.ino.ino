#include <AFMotor.h>
#include <SoftwareSerial.h>

// Define SoftwareSerial pins for HC-05
SoftwareSerial BT(10, 9);  // TX=10(1), RX=9(2)

// Motors
AF_DCMotor motorFRight(1);
AF_DCMotor motorFLeft(2);
AF_DCMotor motorBLeft(3);
AF_DCMotor motorBRight(4);
char command[10];      // buffer for incoming command
int index = 0;         // buffer index
int motorSpeed = 200;  // default speed (0-255)

// Motor helpers
void moveForward() {
  motorFRight.setSpeed(motorSpeed);
  motorFLeft.setSpeed(motorSpeed);
  motorBLeft.setSpeed(motorSpeed);
  motorBRight.setSpeed(motorSpeed);
  motorFRight.run(FORWARD);
  motorFLeft.run(FORWARD);
  motorBLeft.run(FORWARD);
  motorBRight.run(FORWARD);
}

void reverseRobot() {
  motorFRight.setSpeed(motorSpeed);
  motorFLeft.setSpeed(motorSpeed);
  motorBLeft.setSpeed(motorSpeed);
  motorBRight.setSpeed(motorSpeed);
  motorFRight.run(BACKWARD);
  motorFLeft.run(BACKWARD);
  motorBLeft.run(BACKWARD);
  motorBRight.run(BACKWARD);
}

void stopRobot() {
  motorFRight.run(RELEASE);
  motorFLeft.run(RELEASE);
  motorBLeft.run(RELEASE);
  motorBRight.run(RELEASE);
}

void turnLeftSmooth() {
  motorFRight.setSpeed(motorSpeed);
  motorFLeft.setSpeed(motorSpeed);
  motorBLeft.setSpeed(motorSpeed);
  motorBRight.setSpeed(motorSpeed);
  motorFRight.run(FORWARD);
  motorFLeft.run(BACKWARD);
  motorBLeft.run(BACKWARD);
  motorBRight.run(FORWARD);
}

void turnRightSmooth() {
  motorFRight.setSpeed(motorSpeed);
  motorFLeft.setSpeed(motorSpeed);
  motorBLeft.setSpeed(motorSpeed);
  motorBRight.setSpeed(motorSpeed);
  motorFRight.run(BACKWARD);
  motorFLeft.run(FORWARD);
  motorBLeft.run(FORWARD);
  motorBRight.run(BACKWARD);
}


void setup() {
  Serial.begin(9600);
  BT.begin(9600);
}

void loop() {

  // Read incoming Bluetooth commands
  while (BT.available() > 0) {
    char c = BT.read();
    Serial.println(c);
    switch (c) {
      case 'F':
        Serial.println("Forward");
        moveForward();
        break;
      case 'B':
        Serial.println("Backward");
        reverseRobot();
        break;
      case 'R':
        turnRightSmooth();
        break;
      case 'L':
        Serial.println("Left");
        turnLeftSmooth();
        break;
      case 'S':
        Serial.println("Stop");
        stopRobot();
        break;
      case '0':
        motorSpeed = 0;
        break;
      case '1':
        motorSpeed = 25;
        break;
      case '2':
        motorSpeed = 50;
        break;

      case '3':
        motorSpeed = 75;
        break;
      case '4':
        motorSpeed = 100;
        break;
      case '5':
        motorSpeed = 125;
        break;
      case '6':
        motorSpeed = 150;
        break;
      case '7':
        motorSpeed = 175;
        break;

      case '8':
        motorSpeed = 200;
        break;
      case '9':
        motorSpeed = 255;
        break;
    }
  }
}