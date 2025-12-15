int value = 1;
int dt = 1000;
void setup()
{
    // put your setup code here, to run once:
    Serial.begin(9600);
}

void loop()
{
    // put your main code here, to run repeatedly:
    delay(dt);
    Serial.print(value);
    Serial.println(" rex est yeshuava te amo .. ");
    value += 1;
    delay(dt);
}
