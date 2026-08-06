int led = 2;
int led_d4 = 4;
int led_d16 = 16;
int dt = 100;
void setup() {
  // put your setup code here, to run once:
  pinMode(led, OUTPUT);
  pinMode(led_d4, OUTPUT);
  pinMode(led_d16, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(led, HIGH);
  Serial.println("High");
  delay(dt);
  digitalWrite(led, LOW);
  Serial.println("Low");
  delay(dt);
  digitalWrite(led_d4, HIGH);
  Serial.println("High");
  delay(dt);
  digitalWrite(led_d4, LOW);
  Serial.println("Low");
  delay(dt);
  digitalWrite(led_d16, HIGH);
  Serial.println("High");
  delay(dt);
  digitalWrite(led_d16, LOW);
  Serial.println("Low");
}
