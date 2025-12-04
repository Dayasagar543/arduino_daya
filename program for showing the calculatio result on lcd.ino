#include <LiquidCrystal.h>

int r5=7;
int enable=8;
int databus4=9;
int databus5=10;
int databus6=11;
int databus7=12;
int dt=5000;
int num1,num2,result;

LiquidCrystal lcd(r5,enable,databus4,databus5,databus6,databus7);
void setup()
{
  lcd.begin(16,2);
  Serial.begin(9600);
}

void loop()
{
  lcd.setCursor(0,0);
  lcd.print("hi there");
  delay(dt);
  lcd.clear();
  Serial.println("Enter 1st value:");
  while (Serial.available() == 0) {
        
  }
  int num1 = Serial.parseInt(); // Example for reading an integer
  Serial.print("You entered: ");
  Serial.println(num1);
  Serial.println("Enter 2nd value:");
  while (Serial.available() == 0) {
        
  }
  int num2 =Serial.parseInt();
  Serial.print("You entered: ");
  Serial.println(num2);
  
  
  lcd.setCursor(0,0);
  lcd.print("the result is:");
  lcd.setCursor(0,1);
  result=num1+num2;
  lcd.print(result);
  delay(dt);
  lcd.clear();
  
}