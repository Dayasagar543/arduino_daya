// C++ code
//
int button = 7;
void setup()
{
    pinMode(13, OUTPUT);
    pinMode(button, INPUT);
    Serial.begin(9600);
}

void loop()
{
    Serial.println(digitalRead(button));
    if (digitalRead(button) == HIGH)
    {
        digitalWrite(13, HIGH);
    }
    else
    {
        digitalWrite(13, LOW);
    }
}