int led_pin=2;
int dt=5000;
void setup() {
  // put your setup code here, to run once:
  pinMode(led_pin,OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(led_pin,HIGH);
  delay(dt);
  digitalWrite(led_pin,LOW);
  delay(dt);

}
