// C++ code
// comparision operators
int var1 = 7;
int var2 = 8;
int var3 = 7;
void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(9500);
    if (var1 > var2)
    {
        Serial.println("var1 is great");
    }
    if (var1 < var2)
    {
        Serial.println("var2 is great");
        if (var1 >= var2)
        {
            Serial.println("var1 is either great or equal to var1");
        }
        else
        {
            Serial.println("var is either less or equal to var1");
        }
    }
    if (var1 == var3)
    {
        Serial.println("var3 is equal to var1");
    }
    if (var2 >= var1)
    {
        Serial.println("the condition is true var2 is greater than var1");
    }
    if (var1 <= var2)
    {
        Serial.println("the condition is true var1 is less than var2");
    }
    if (var1 != var2)
    {
        Serial.println("the condtion is true var1 is not eqaul to var2");
    }

    Serial.println(var1 > var2);
    Serial.println(var1 < var2);
    Serial.println(var1 != var2);
    Serial.println(var1 == var2);
    Serial.println(var1 >= var2);
    Serial.println(var1 <= var2);

    // and , or , not operator
    Serial.println("printing the result of and operation");
    Serial.println(var1 == var3 && var1 < var2);
    Serial.println("printing the result of or operation");
    Serial.println(var1 == var3 || var1 > var2);
    Serial.println("printing the result of not ! operation");
    Serial.println(!false);
    Serial.println(!true);
}

void loop()
{
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000); // Wait for 1000 millisecond(s)
    digitalWrite(LED_BUILTIN, LOW);
    delay(1000); // Wait for 1000 millisecond(s)
                 // static int num1=20;
    // Serial.println(num1++);
}