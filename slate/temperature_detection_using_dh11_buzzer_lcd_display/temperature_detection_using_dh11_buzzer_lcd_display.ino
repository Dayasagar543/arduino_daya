
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

// Pin configuration
#define DHTPIN 2
#define DHTTYPE DHT11
#define BUZZER 8

// LCD address, columns, rows
LiquidCrystal_I2C lcd(0x27, 16, 2);
DHT dht(DHTPIN, DHTTYPE);

// Alarm limits
const float MAX_TEMP = 35.0;
const float MAX_HUMIDITY = 70.0;

void setup() {
  Serial.begin(9600);

  pinMode(BUZZER, OUTPUT);
  digitalWrite(BUZZER, LOW);

  lcd.init();
  lcd.backlight();

  dht.begin();

  lcd.setCursor(0, 0);
  lcd.print("Temp & Humidity");
  lcd.setCursor(0, 1);
  lcd.print("System Starting");
  delay(2000);
  lcd.clear();
}

void loop() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Check for failed sensor readings
  if (isnan(temperature) || isnan(humidity)) {
    lcd.setCursor(0, 0);
    lcd.print("Sensor Error    ");
    lcd.setCursor(0, 1);
    lcd.print("Check DHT11     ");

    digitalWrite(BUZZER, LOW);
    Serial.println("Failed to read DHT11");
    delay(2000);
    return;
  }

  // Display readings
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature, 1);
  lcd.print((char)223);
  lcd.print("C   ");

  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.print(humidity, 0);
  lcd.print("%   ");

  // Alarm if either limit is exceeded
  if (temperature >= MAX_TEMP ||
      humidity >= MAX_HUMIDITY) {
    digitalWrite(BUZZER, HIGH);
    Serial.println("WARNING: Limit exceeded!");
  } else {
    digitalWrite(BUZZER, LOW);
    Serial.println("Conditions normal");
  }

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" C | Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  delay(2000);
}
