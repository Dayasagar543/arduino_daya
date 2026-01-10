#include "DHT.h"

#define dht_pin 2
#define DHTTYPE DHT11
float temperaturec;
float temperaturef;
float humidity;

DHT dht(dht_pin, DHTTYPE);
void setup()
{
    // put your setup code here, to run once:
    Serial.begin(9600);
    dht.begin();
}

void loop()
{
    // put your main code here, to run repeatedly:
    temperaturec = dht.readTemperature();
    temperaturef = dht.readTemperature(true);
    humidity = dht.readHumidity();
    Serial.print("the temperature in centigrade is ");
    Serial.print(temperaturec);
    Serial.print(" the temperature in farenite is ");
    Serial.print(temperaturef);
    Serial.print(" the humidity is ");
    Serial.print(humidity);
    Serial.println();
}
