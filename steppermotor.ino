#include <Stepper.h>
int steps_per_revolution = 2048;
int dt = 2000;
int motorspeed = 10;
Stepper step(steps_per_revolution, 3, 5, 4, 6);

void setup()
{
    // put your setup code here, to run once:
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
    Serial.begin(9600);
    step.setSpeed(motorspeed);
}

void loop()
{
    // put your main code here, to run repeatedly:
    step.step(steps_per_revolution);
    delay(dt);
    step.step(-steps_per_revolution);
    delay(dt);
}
