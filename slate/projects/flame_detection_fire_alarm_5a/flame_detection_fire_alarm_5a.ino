
const int flamePin = 2;
const int ledPin = 5;
const int buzzerPin = 6;

void setup() {
  pinMode(flamePin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  int flameState = digitalRead(flamePin);

  // Many flame sensor modules output LOW when flame is detected
  if (flameState == LOW) {
    digitalWrite(ledPin, HIGH);
    digitalWrite(buzzerPin, HIGH);

    Serial.println("FIRE DETECTED!");
  } else {
    digitalWrite(ledPin, LOW);
    digitalWrite(buzzerPin, LOW);

    Serial.println("No flame detected");
  }

  delay(200);
}
