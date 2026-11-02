#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

// LCD I2C address (change 0x27 to 0x3F if needed)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// DHT11 settings
#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  lcd.init();          // Initialize LCD
  lcd.backlight();     // Turn on backlight

  dht.begin();         // Initialize DHT11

  lcd.setCursor(0, 0);
  lcd.print("DHT11 Starting");
  delay(2000);
  lcd.clear();
}

void loop() {
  float temperature = dht.readTemperature(); // Celsius
  float humidity = dht.readHumidity();

  lcd.clear();

  if (isnan(temperature) || isnan(humidity)) {
    lcd.setCursor(0, 0);
    lcd.print("Sensor Error");
  } else {
    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(temperature);
    lcd.print((char)223);   // Degree symbol
    lcd.print("C");

    lcd.setCursor(0, 1);
    lcd.print("Hum: ");
    lcd.print(humidity);
    lcd.print("%");
  }

  delay(2000);
}