// C++ code
//

int pin = 9, delay_val = 0, range_val = 255;
void setup()
{
    pinMode(pin, OUTPUT);
    Serial.begin(9600);
}

void loop()
{
    analogWrite(pin, 100); // for analog we can use the range not
    // high and low but we can use 0 as low and 255 as high or any
    // range between
    blinking_led(pin, delay_val, range_val);
}

void blinking_led(int pin, int delay_val, int range_val)
{

    for (int i = 0; i <= range_val; i++)
    {
        analogWrite(pin, i);
        delay(delay_val);
        Serial.println(i);
    }
    for (int i = range_val; i >= 0; i--)
    {
        analogWrite(pin, i);
        delay(delay_val);
        Serial.println(i);
    }
}