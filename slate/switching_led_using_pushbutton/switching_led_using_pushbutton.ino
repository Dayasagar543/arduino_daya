int ledPin = 5;
int switchPin = 3;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(switchPin, INPUT_PULLUP);
}

void loop() {

  int switchState = digitalRead(switchPin);

  if (switchState == LOW) {
    digitalWrite(ledPin, HIGH);  // Turn LED ON
  }
  else {
    digitalWrite(ledPin, LOW);   // Turn LED OFF
  }
}