#include<LiquidCrystal.h>
#include<DHT.h>       
#define DHTTYPE DHT11

int db7=12;
int db6=11;
int db5=10;
int db4=9;
int enable=8;
int rs=7;
int dht=2;
int dt=2000;
float temperaturec;
float temperatureF;
float humidity;

LiquidCrystal lcd(rs,enable,db4,db5,db6,db7) ;
DHT ht(dht,DHTTYPE)

void setup(){
Serial.begin(9600);
ht.begin()
lcd.begin(16, 2);
}

void loop(){
  lcd.setCursor(0, 1);
  delay(dt);
  lcd.print("hello tej");
  lcd.clear();
  delay(dt);
  temperaturec=ht.readTemperature();
  temperatureF=ht.readTemperature(true);
  humidity=ht.readHumidity();
  lcd.setCursor(0, 0)
  lcd.print("the temperature in centigrade  is");
  lcd.setCursor(0, 1);
  lcd.print(temperaturec);
  delay(dt);
  lcd.clear();
  lcd.setCursor(0, 0)
  lcd.print("the temperature in Farenite  is");
  lcd.setCursor(0, 1);
  lcd.print(temperatureF);
  delay(dt);
  lcd.clear();
  lcd.setCursor(0, 0)
  lcd.print("the temperature in Humidity is");
  lcd.setCursor(0, 1);
  lcd.print(humidity);
  delay(dt);
  lcd.clear();
  
}