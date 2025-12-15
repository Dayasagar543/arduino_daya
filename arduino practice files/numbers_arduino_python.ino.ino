int value = 1, value2 = 3, value3 = 10;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop()
{
  // put your main code here, to run repeatedly:

  value += 1;
  value2 += 3;
  value3 += 4;
  Serial.print("the value1 ");
  Serial.print(value);
  Serial.print(" the value2 ");
  Serial.print(value2);
  Serial.print(" the value3 ");
  Serial.println(value3);
}
