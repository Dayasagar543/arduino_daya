
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11

const int buzzerPin = 6;
const int fanPin = 10;

// Change 0x27 to 0x3F if your LCD uses that address
LiquidCrystal_I2C lcd(0x27, 16, 2);
DHT dht(DHTPIN, DHTTYPE);

const float FAN_ON_TEMP = 30.0;
const float FAN_OFF_TEMP = 28.0;
const float MAX_TEMP = 35.0;
const float MAX_HUMIDITY = 80.0;

bool fanOn = false;

void setup() {
  Serial.begin(9600);

  pinMode(buzzerPin, OUTPUT);
  pinMode(fanPin, OUTPUT);

  digitalWrite(buzzerPin, LOW);
  digitalWrite(fanPin, LOW);

  lcd.init();
  lcd.backlight();

  dht.begin();

  lcd.setCursor(0, 0);
  lcd.print("Temp & Humidity");
  lcd.setCursor(0, 1);
  lcd.print("Control System");
  delay(2000);
  lcd.clear();
}

void loop() {
  float temp = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (isnan(temp) || isnan(humidity)) {
    lcd.setCursor(0, 0);
    lcd.print("DHT11 Error     ");
    lcd.setCursor(0, 1);
    lcd.print("Check Wiring    ");

    // Stop outputs if sensor readings fail
    fanOn = false;
    digitalWrite(fanPin, LOW);
    digitalWrite(buzzerPin, LOW);

    delay(2000);
    return;
  }

  // Fan control with hysteresis
  if (temp >= FAN_ON_TEMP) {
    fanOn = true;
  } else if (temp <= FAN_OFF_TEMP) {
    fanOn = false;
  }

  // High temperature or humidity alarm
  if (temp >= MAX_TEMP || humidity >= MAX_HUMIDITY) {
    digitalWrite(buzzerPin, HIGH);
  } else {
    digitalWrite(buzzerPin, LOW);
  }

  digitalWrite(fanPin, fanOn ? HIGH : LOW);

  // Display readings
  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(temp, 1);
  lcd.print((char)223);
  lcd.print("C H:");
  lcd.print(humidity, 0);
  lcd.print("%  ");

  lcd.setCursor(0, 1);
  lcd.print("Fan:");
  lcd.print(fanOn ? "ON " : "OFF");
  lcd.print(" Alarm:");
  lcd.print(
    (temp >= MAX_TEMP ||
     humidity >= MAX_HUMIDITY) ? "ON " : "OFF"
  );

  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.print(" C | Humidity: ");
  Serial.print(humidity);
  Serial.print(" % | Fan: ");
  Serial.println(fanOn ? "ON" : "OFF");

  delay(2000);
}
