
void setup()
{

    // activating the serial buzz
    Serial.begin(9600);

    // arrays
    int array[5] = {1, 2, 4, 5, 6};
    Serial.println("printing the 2nd value of the array");
    Serial.println(array[1]);
    Serial.println("printing the  values of the array");
    for (int i = 0; i < 5; i++)
    {
        Serial.println(array[i]);
    }
    Serial.print("printing the sum of  values of the array  ");
    int sum = 0;
    for (int i = 0; i < 5; i++)
    {
        sum += array[i];
    }
    Serial.print(sum);

    // strings

    char str1[7] = {'a', 's', 'h', 'i', 's', 'h'};
    Serial.println(str1);
    char str2[7] = {'a', 's', 'h', 'i', 's', 'h', '\0'};
    Serial.println(str2);
    char str3[] = "ashish";
    Serial.println(str3);
    char str4[7] = "ashish";
    Serial.println(str4);
    String str5 = "ashish";
    Serial.println(str5);
    Serial.println(str5.charAt(0));
}

void loop()
{
    blink();
}

// functions
void blink()
{
    //  Serial.begin(9600);
    Serial.println("making the led glow");
    digitalWrite(13, HIGH);
    delay(2000);
    Serial.println("making the led turn off");
    digitalWrite(13, LOW);
    delay(2000);
}
