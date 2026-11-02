
const int irPin = 2;
const int ledPin = 5;
const int buzzerPin = 6;

void setup() {
  pinMode(irPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  int sensorValue = digitalRead(irPin);

  // Most IR obstacle sensors output LOW
  // when an object is detected.
  if (sensorValue == LOW) {
    digitalWrite(ledPin, HIGH);

    tone(buzzerPin, 1000);  // 1 kHz alarm
    Serial.println("INTRUSION DETECTED!");
  } 
  else {
    digitalWrite(ledPin, LOW);

    noTone(buzzerPin);
    Serial.println("Area secure");
  }

  delay(100);
}
