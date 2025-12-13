int trigger_pin = 6;
int echo_pin = 7;
int travel_echo;
int dt = 10;

void setup()
{
    pinMode(trigger_pin, OUTPUT);
    pinMode(echo_pin, INPUT);
    Serial.begin(9600);
}

void loop()
{

    digitalWrite(trigger_pin, LOW);
    delayMicroseconds(dt);
    digitalWrite(trigger_pin, HIGH);
    delayMicroseconds(dt);
    digitalWrite(trigger_pin, LOW);
    delayMicroseconds(dt);
    travel_echo = pulseIn(echo_pin, HIGH);
    Serial.println(travel_echo);
    delay(25);
}