
const int trigPin = 9;
const int echoPin = 10;
const int ledPin = 5;
const int buzzerPin = 6;

const int detectionDistance = 50; // centimetres

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  // Send an ultrasonic pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the returning echo
  long duration = pulseIn(echoPin, HIGH, 30000);

  if (duration == 0) {
    digitalWrite(ledPin, LOW);
    noTone(buzzerPin);
    Serial.println("No object detected");
  } else {
    float distance = duration * 0.0343 / 2;

    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    if (distance <= detectionDistance) {
      digitalWrite(ledPin, HIGH);
      tone(buzzerPin, 1000);
      Serial.println("INTRUSION DETECTED!");
    } else {
      digitalWrite(ledPin, LOW);
      noTone(buzzerPin);
      Serial.println("Area secure");
    }
  }

  delay(100);
}
