#include <Servo.h>
int servo_pin = 9;
int ir_pin = 7;
int dt = 100;
int starting_angle = 50;
int ending_angle = 180;
Servo myservo;

void setup() {
  // put your setup code here, to run once:
  myservo.attach(servo_pin);
  pinMode(ir_pin, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int ir_Read_value = digitalRead(ir_pin);
  Serial.println(ir_Read_value);

  if (ir_Read_value == 0) {
    moveto_starting_angle();
  } else {
    moveto_ending_angle();
  }
  delay(dt);
}

void moveto_ending_angle() {
  for (int angle = starting_angle; angle < ending_angle; angle++) {
    myservo.write(angle);
  }
}
void moveto_starting_angle() {
  for (int angle = ending_angle; angle > starting_angle; angle--) {
    myservo.write(angle);
  }
}
