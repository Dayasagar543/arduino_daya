
#include <LiquidCrystal.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTTYPE DHT11

int db7 = 12;
int db6 = 11;
int db5 = 10;
int db4 = 9;
int enable = 8;
int rs = 7;
int dhtPin = 2;
int dt = 2000;

float temperatureC;
float temperatureF;
float humidity;

LiquidCrystal lcd(rs, enable, db4, db5, db6, db7);
DHT ht(dhtPin, DHTTYPE);

void setup() {
  Serial.begin(9600);
  ht.begin();
  lcd.begin(16, 2);
}

void loop() {
  // Print hello first
  lcd.setCursor(0, 0);
  lcd.print("Todays");
  lcd.setCursor(0, 1);
  lcd.print("weather");
  delay(dt);
  lcd.clear();

  // Read sensor data
  temperatureC = ht.readTemperature();
  temperatureF = ht.readTemperature(true);
  humidity = ht.readHumidity();

  // Display temperature in Celsius
  lcd.setCursor(0, 0);
  lcd.print("Temp C:");
  lcd.setCursor(0, 1);
  lcd.print(temperatureC);
  delay(dt);
  lcd.clear();

  // Display temperature in Fahrenheit
  lcd.setCursor(0, 0);
  lcd.print("Temp F:");
  lcd.setCursor(0, 1);
  lcd.print(temperatureF);
  delay(dt);
  lcd.clear();

  // Display humidity
  lcd.setCursor(0, 0);
  lcd.print("Humidity:");
  lcd.setCursor(0, 1);
  lcd.print(humidity);
  delay(dt);
  lcd.clear();
}
