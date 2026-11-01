#include <AFMotor.h>

//obstacle values
int left_side = A0;
int center = A1;
int right_side = A2;

//depth avaoider
int depth_right = A3;
int depth_center = A4;
int depth_left = A5;

AF_DCMotor Motor1(1, MOTOR12_1KHZ);  // create motor #1 using M1 output on Motor Drive Shield, set to 1kHz PWM frequency
AF_DCMotor Motor2(2, MOTOR12_1KHZ);  // create motor #2, using M2 output, set to 1kHz PWM frequency


void setup() {
  //obstacle values
  pinMode(left_side, INPUT);
  pinMode(center, INPUT);
  pinMode(right_side, INPUT);
  //depth avaoider
  pinMode(depth_right, INPUT);
  pinMode(depth_center, INPUT);
  pinMode(depth_left, INPUT);
  forward();
}

void loop() {
  //obstacle values
  int ls = digitalRead(left_side);
  int cs = digitalRead(center);
  int rs = digitalRead(right_side);
  //depth avaoider
  int dr = digitalRead(depth_right);
  int dc = digitalRead(depth_center);
  int dl = digitalRead(depth_left);

  //logic
  if (ls == HIGH && cs == HIGH && rs == HIGH) {
    forward();
  } else if (ls == LOW && cs == HIGH && rs == HIGH) {
    right();
  } else if (ls == HIGH && cs == HIGH && rs == LOW) {
    left();
  } else if (ls == HIGH && cs == LOW && rs == HIGH) {
    reverse();
    delay(500);
    left();
    delay(500);
  } else if (ls == LOW && cs == LOW && rs == HIGH) {
    reverse();
    delay(500);
    right();
    delay(500);
  } else if (ls == HIGH && cs == LOW && rs == LOW) {
    reverse();
    delay(500);
    left();
    delay(500);
  } else if (ls == LOW && cs == HIGH && rs == LOW) {
    reverse();
    delay(500);
    left();
    delay(500);
  } else if (ls == LOW && cs == LOW && rs == LOW) {
    reverse();
    delay(500);
    left();
    delay(500);
  }
}
void forward() {
  Motor1.run(FORWARD);
  Motor2.run(FORWARD);
  Motor1.setSpeed(130);
  Motor2.setSpeed(130);
}
void reverse() {
  Motor1.run(BACKWARD);
  Motor2.run(BACKWARD);
  Motor1.setSpeed(130);
  Motor2.setSpeed(130);
}
void right() {
  Motor1.run(FORWARD);
  Motor2.run(BACKWARD);
  Motor1.setSpeed(130);
  Motor2.setSpeed(130);
}
void left() {
  Motor1.run(BACKWARD);
  Motor2.run(FORWARD);
  Motor1.setSpeed(130);
  Motor2.setSpeed(130);
}
void stp() {
  Motor1.run(RELEASE);
  Motor2.run(RELEASE);
  Motor1.setSpeed(0);
  Motor2.setSpeed(0);
}
void stpleft() {
  Motor1.run(FORWARD);
  Motor2.run(RELEASE);
  Motor1.setSpeed(130);
  Motor2.setSpeed(0);
}
void stpright() {
  Motor1.run(RELEASE);
  Motor2.run(FORWARD);
  Motor1.setSpeed(0);
  Motor2.setSpeed(130);
}
