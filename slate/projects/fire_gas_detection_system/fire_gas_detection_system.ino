int led = 13;
int buzzer = 7;
int flame_sensor = 2;
int gas_sensor = A0;
int dt = 500;

void setup() {
  Serial.begin(9600);

  pinMode(led, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(flame_sensor, INPUT);
}

void loop() {

  int flame_value = digitalRead(flame_sensor);
  int gas_value = analogRead(gas_sensor);

  Serial.print("Flame: ");
  Serial.println(flame_value);

  Serial.print("Gas: ");
  Serial.println(gas_value);

  // Turn on alarm if flame OR gas is detected
  if (flame_value == LOW || gas_value >= 50) {
    digitalWrite(led, HIGH);
    digitalWrite(buzzer, HIGH);
  } else {
    digitalWrite(led, LOW);
    digitalWrite(buzzer, LOW);
  }

  delay(dt);
}