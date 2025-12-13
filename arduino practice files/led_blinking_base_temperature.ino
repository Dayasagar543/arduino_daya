int temperature = -30;

void setup()
{
    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
    pinMode(13, OUTPUT);
    Serial.begin(9600);
}

void loop()
{
    if (temperature >= 5 && temperature <= 35)
    {
        Serial.println("the temperature is approxmate room temperature");
        digitalWrite(6, HIGH);
        delay(2000);
        digitalWrite(6, LOW);
        delay(2000);
    }
    else if (temperature >= 31 && temperature <= 100)
    {
        Serial.println("the temperature is rising to boiling");
        digitalWrite(5, HIGH);
        delay(1500);
        digitalWrite(5, LOW);
        delay(1500);
    }
    else if (temperature >= 101)
    {
        Serial.println("the temperature is above boiling please watch and monitor");
        digitalWrite(4, HIGH);
        delay(1000);
        digitalWrite(4, LOW);
        delay(1000);
    }
    else
    {
        Serial.print("the temperature is cold");
        digitalWrite(13, HIGH);
        delay(700);
        digitalWrite(13, LOW);
        delay(700);
    }
}