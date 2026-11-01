#include <Servo.h>
int servo_pin = 9;
// Pin definitions
const int trigPin = 11;   // Trigger pin of HC-SR04
const int echoPin = 10;   // Echo pin of HC-SR04
const int buzzerPin = 4;  // Buzzer pin
int dt = 100;
int starting_angle = 5;
int ending_angle = 120;
Servo myservo;


// Variables
long duration;
float distance;

void setup() {
  // put your setup code here, to run once:
  myservo.attach(servo_pin);
  Serial.begin(9600);  // Start serial communication
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  // Send ultrasonic pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read echo time
  duration = pulseIn(echoPin, HIGH, 30000UL);  // Timeout after 30ms (~5m range)

  // Calculate distance in cm
  distance = duration * 0.0343 / 2;

  // Display distance
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Detection logic
  if (distance > 0 && distance < 10) {  // Valid reading and less than 10 cm
    moveto_ending_angle();
    digitalWrite(buzzerPin, HIGH);
  } else {
    moveto_starting_angle();
    digitalWrite(buzzerPin, LOW);
  }

  delay(200);  // Small delay for stability
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













