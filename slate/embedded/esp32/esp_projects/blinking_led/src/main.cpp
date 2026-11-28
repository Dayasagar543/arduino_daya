#include <Arduino.h>

int led=2;
int dt=50;


void setup() {
  // put your setup code here, to run once:
pinMode(led,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(led,HIGH);
  delay(dt);

  digitalWrite(led,LOW);
  delay(dt);
}

// put function definitions here:
