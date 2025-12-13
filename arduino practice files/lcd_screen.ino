#include <LiquidCrystal.h>

// C++ code
//

int rs = 7;
int en = 8;
int databus4 = 9;
int databus5 = 10;
int databus6 = 11;
int databus7 = 12;
int dt = 1000;
LiquidCrystal lcd(rs, en, databus4, databus5, databus6, databus7);
void setup()
{
    lcd.begin(16, 2);
}

void loop()
{
    delay(dt);
    lcd.setCursor(0, 0);
    lcd.print("hellow world");
    delay(dt);
    lcd.clear();
    // lcd.setCursor(0,1);
    // lcd.setCursor(0,0);
    // lcd.print("hellow my name is regex");
    // delay(dt);
    // lcd.clear();
    for (int i = 0; i < 255; i++)
    {
        lcd.setCursor(0, 0);
        lcd.print(i);
        delay(500);
        lcd.clear();
    }
}