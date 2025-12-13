#include <Stepper.h>
int steps_per_revolution = 2048;
int pin_read = 11;
int dt = 2000;
int motorspeed = 10;
int motor_direction = 1;
int oldstate = 1;
int newstate;
Stepper step(steps_per_revolution, 3, 5, 4, 6);

void setup()
{
    // put your setup code here, to run once:
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
    pinMode(pin_read, INPUT);
    Serial.begin(9600);
    step.setSpeed(motorspeed);
}

void loop()
{
    // put your main code here, to run repeatedly:
    //  step.step(steps_per_revolution);
    //  delay(dt);
    //  step.step(-steps_per_revolution);
    //  delay(dt);
    int newstate = digitalRead(pin_read);
    Serial.println(newstate);
    if (oldstate == 1 && newstate == 0)
    {
        motor_direction = motor_direction * -1;
    }
    step.step(1 * motor_direction);
    oldstate = newstate;
}
