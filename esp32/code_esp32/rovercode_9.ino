#include <WiFi.h>
#include <WiFiAP.h>
#include <WiFiClient.h>
#include <WiFiGeneric.h>
#include <WiFiMulti.h>
#include <WiFiSTA.h>
#include <WiFiScan.h>
#include <WiFiServer.h>
#include <WiFiType.h>
#include <WiFiUdp.h>

#include <HTTP_Method.h>
#include <Middlewares.h>
#include <Uri.h>
#include <WebServer.h>
#include <esp_wifi.h>
#include <ESP32Servo.h>

const char *ssid = "rover";
const char *password = "12345";

WebServer server(80);
Servo scanServo;

// Motor pins
#define ENA 16
#define IN1 17
#define IN2 5
#define IN3 18
#define IN4 19
#define ENB 21

// ultrasonic

#define TRIG 25
#define ECHO 26
#define SERVO_PIN 13

// CALIBRATION

int baseSpeed = 200;
int leftBoost = 255;
int rightBoost = 255;

// Modes
enum Mode {
  MANUAL,
  OBSTACLE,
  FOLLOW
};

Mode currentMode = MANUAL;

unsigned long lastScanTime = 0;
unsigned long lastFollowTime = 0;
int LeftDist = 0, rightDist = 0;

long getDistance() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  long duration = pulseIn(ECHO, HIGH, 15000);
  if (duration == 0)
    return 400;
  return duration * 0.034 / 2;
}

void setLeft(int spd) {
  ledcWrite(ENA, spd);
}
void setRight(int spd) {
  ledcWrite(ENB, spd);
}

void kickStart() {
  setRight(rightBoost);
  setLeft(leftBoost);
  delay(300);  // boosting intially
  setLeft(baseSpeed);
  setRight(baseSpeed);
}

void stopMotors() {
  setLeft(0);
  setRight(0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
void forward() {
  kickStart();
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
void backward() {
  kickStart();
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
void Left() {

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
void Right() {

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void obstacleMode() {
  // prevent spamming the sensor
  if (millis() - lastScanTime < 60)
    return;
  lastScanTime = millis();

  int front = getDistance();
  if (front > 0 && front < 25) {
    // stops and moves back slightly
    stopMotors();
    delay(200);
    backward();
    delay(300);
    stopMotors();
    delay(200);

    // looking left
    scanServo.write(170);
    delay(500);  // wait for servo to get there
    long leftDist = getDistance();
    // looking Right
    scanServo.write(10);
    delay(500);
    long rightDist = getDistance();
    // center Servo
    scanServo.write(90);
    delay(300);

    // make a decision
    if (leftDist >= rightDist) {
      Left();
      delay(400);
    } else {
      Right();
      delay(400);
    }

    stopMotors();
    delay(200);
  } else {
    // path is clear
    forward();
  }
}

void followMode() {
  if (millis() - lastFollowTime < 60)
    return;
  lastFollowTime = millis();

  long distance = getDistance();

  // out of range or lost target

  if (distance < 0 || distance > 30) {
    stopMotors();
  }  // Too close ! Back up
  else if (distance < 12) {
    backward();
  }  // perfect distance , just stop and wait
  else if (distance >= 12 && distance <= 20) {
    stopMotors();
  }  // target is moving away  follow it
  else if (distance > 20 && distance <= 30) {
    forward();
  }
}

///----------------APP Handlers--------

void handleSpecialMode() {
  String path = server.uri();
  String level = server.arg("level");

  if (level == "1") {
    if (path == "/avoid")
      currentMode = OBSTACLE;
    else if (path == "/follow")
      currentMode = FOLLOW;
  } else {
    // if elve is 0, rever back to manual control and stop
    currentMode = MANUAL;
    stopMotors();
  }

  // Ensure servo faces forward when changing modes
  scanServo.write(90);
  Serial.print("APP triggered");
  Serial.print(path);
  Serial.print(" | Level: ");
  Serial.print(level);
  server.send(200, "text/plain", "OK");
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  ledcAttach(ENA, 1000, 8);
  ledcAttach(ENB, 1000, 8);

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  ESP32PWM::allocateTimer(2);
  scanServo.setPeriodHertz(50);
  scanServo.attach(SERVO_PIN, 500, 2400);
  scanServo.write(90);

  WiFi.softAP(ssid, password);
  WiFi.setSleep(false);


  Serial.print("AP IP Address: ");
  Serial.println(WiFi.softAPIP());  // Usually prints 192.168.4.1

  // way Manual directions

  server.on("/f", []() {
    currentMode = MANUAL;
    forward();
    server.send(200);
  });
  server.on("/b", []() {
    currentMode = MANUAL;
    backward();
    server.send(200);
  });
  server.on("/s", []() {
    currentMode = MANUAL;
    stopMotors();
    server.send(200);
  });

  // soft turns (Diagonals)
  server.on("/l", []() {
    currentMode = MANUAL;
    Left();
    server.send(200);
  });
  server.on("/r", []() {
    currentMode = MANUAL;
    Right();
    server.send(200);
  });

  // special functions
  server.on("/horn", handleSpecialMode);
  server.on("/track", handleSpecialMode);
  server.on("/avoid", handleSpecialMode);
  server.on("/follow", handleSpecialMode);
  server.begin();
  Serial.println("Server started !!");
}

void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();
  yield();

  if (currentMode == OBSTACLE)
    obstacleMode();
  else if (currentMode == FOLLOW)
    followMode();
}
