#include <AFMotor.h>
#include <SoftwareSerial.h>

// Bluetooth Module
SoftwareSerial BT(10, 9);  // RX, TX

// Motors
AF_DCMotor M1(1, MOTOR12_1KHZ);
AF_DCMotor M2(2, MOTOR12_1KHZ);
AF_DCMotor M3(3, MOTOR34_1KHZ);
AF_DCMotor M4(4, MOTOR34_1KHZ);

char command;
int speed = 200;  // Speed (0-255)

void setup() {
  Serial.begin(9600);
  BT.begin(9600);
  M1.setSpeed(speed);
  M2.setSpeed(speed);
  M3.setSpeed(speed);
  M4.setSpeed(speed);

  stopMotors();

  Serial.println("AT Mode Ready");
}

void loop() {
  if (BT.available()) {
    command = BT.read();
    Serial.println(command);

    switch (command) {
      case 'F':
        Serial.print("forward");
        forward();
        break;

      case 'B':
        Serial.print("backward");
        backward();
        break;

      case 'L':
        Serial.print("left");
        left();
        break;

      case 'R':
        Serial.print("right");
        right();
        break;

      case 'S':
        stopMotors();
        Serial.print("stop");
        break;

      case '+':
        increaseSpeed();
        break;

      case '-':
        decreaseSpeed();
        break;
    }
  }
}

//========================

void forward() {
  M1.run(FORWARD);
  M2.run(FORWARD);
  M3.run(FORWARD);
  M4.run(FORWARD);
}

void backward() {
  M1.run(BACKWARD);
  M2.run(BACKWARD);
  M3.run(BACKWARD);
  M4.run(BACKWARD);
}

void left() {
  M1.run(BACKWARD);
  M2.run(FORWARD);
  M3.run(BACKWARD);
  M4.run(FORWARD);
}

void right() {
  M1.run(FORWARD);
  M2.run(BACKWARD);
  M3.run(FORWARD);
  M4.run(BACKWARD);
}

void stopMotors() {
  M1.run(RELEASE);
  M2.run(RELEASE);
  M3.run(RELEASE);
  M4.run(RELEASE);
}

//========================

void increaseSpeed() {
  speed += 20;

  if (speed > 255)
    speed = 255;

  M1.setSpeed(speed);
  M2.setSpeed(speed);
  M3.setSpeed(speed);
  M4.setSpeed(speed);
}

void decreaseSpeed() {
  speed -= 20;

  if (speed < 0)
    speed = 0;

  M1.setSpeed(speed);
  M2.setSpeed(speed);
  M3.setSpeed(speed);
  M4.setSpeed(speed);
}