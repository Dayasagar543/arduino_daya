const int ldrPin = 2;
const int ledPin = 5;

void setup() {
  pinMode(ldrPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  int ldrState = digitalRead(ldrPin);

  if (ldrState == LOW) {
     digitalWrite(ledPin, LOW);
  } else {
   
    digitalWrite(ledPin, HIGH);
    delay(500);
  }
}