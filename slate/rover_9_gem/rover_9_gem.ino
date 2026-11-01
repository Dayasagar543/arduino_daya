#include <WiFi.h>
#include <WebServer.h>
#include <ESP32Servo.h>
#include <esp_wifi.h>

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

// Ultrasonic
#define TRIG 25
#define ECHO 26
#define SERVO_PIN 13

// Calibration
int baseSpeed = 200;

// Modes
enum Mode
{
    MANUAL,
    OBSTACLE,
    FOLLOW
};

Mode currentMode = MANUAL;

unsigned long lastScanTime = 0;
unsigned long lastFollowTime = 0;

// Forward declarations
void stopMotors();
void forward();
void backward();
void Left();
void Right();

long getDistance()
{
    digitalWrite(TRIG, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG, LOW);

    long duration = pulseIn(ECHO, HIGH, 20000); // 20ms timeout (~3.4m max)
    if (duration == 0)
        return 400; // Return out of range value
    return duration * 0.034 / 2;
}

void setLeft(int speed)
{
    ledcWrite(ENA, speed);
}

void setRight(int speed)
{
    ledcWrite(ENB, speed);
}

// Helper to keep server responsive during non-blocking pauses
void dynamicDelay(int ms)
{
    unsigned long start = millis();
    while (millis() - start < ms)
    {
        server.handleClient();
        yield();
    }
}

void obstacleMode()
{
    if (millis() - lastScanTime < 80)
        return;
    lastScanTime = millis();

    int front = getDistance();
    if (front > 0 && front < 25)
    {
        stopMotors();
        dynamicDelay(150);
        
        backward();
        dynamicDelay(300);
        
        stopMotors();
        dynamicDelay(150);

        // Look left
        scanServo.write(170);
        dynamicDelay(250); // Increased time for physical servo movement
        long leftDist = getDistance();

        // Look right
        scanServo.write(10);
        dynamicDelay(300);
        long rightDist = getDistance();

        // Center servo
        scanServo.write(90);
        dynamicDelay(200);

        // Decide direction
        if (leftDist >= rightDist)
        {
            Left();
            dynamicDelay(400);
        }
        else
        {
            Right();
            dynamicDelay(400);
        }

        stopMotors();
        dynamicDelay(150);
    }
    else
    {
        forward();
    }
}

void followMode()
{
    if (millis() - lastFollowTime < 60)
        return;
    lastFollowTime = millis();

    long distance = getDistance();

    if (distance <= 0 || distance > 35)
    {
        stopMotors();
    }
    else if (distance < 12)
    {
        backward();
    }
    else if (distance >= 12 && distance <= 20)
    {
        stopMotors();
    }
    else if (distance > 20 && distance <= 35)
    {
        forward();
    }
}

void handleSpecialMode()
{
    String path = server.uri();
    String level = server.arg("level");

    if (level == "1")
    {
        if (path == "/avoid")
            currentMode = OBSTACLE;
        else if (path == "/follow")
            currentMode = FOLLOW;
    }
    else
    {
        currentMode = MANUAL;
        stopMotors();
    }

    scanServo.write(90);
    server.send(200, "text/plain", "OK");
}

void setup()
{
    Serial.begin(115200);
    
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);

    // PWM Setup (Arduino ESP32 Core v3.x style)
    ledcAttach(ENA, 1000, 8);
    ledcAttach(ENB, 1000, 8);

    pinMode(TRIG, OUTPUT);
    pinMode(ECHO, INPUT);

    // Allow ESP32Servo to manage timers automatically
    ESP32PWM::allocateTimer(0);
    ESP32PWM::allocateTimer(1);
    ESP32PWM::allocateTimer(2);
    ESP32PWM::allocateTimer(3);
    
    scanServo.setPeriodHertz(50);
    scanServo.attach(SERVO_PIN, 500, 2400);
    scanServo.write(90);

    WiFi.softAP(ssid, password);
    WiFi.setSleep(false);

    Serial.print("AP IP Address: ");
    Serial.println(WiFi.softAPIP());

    // Manual control endpoints
    server.on("/f", []() {
        currentMode = MANUAL;
        forward();
        server.send(200, "text/plain", "Moving Forward");
    });
    server.on("/b", []() {
        currentMode = MANUAL;
        backward();
        server.send(200, "text/plain", "Moving Backward");
    });
    server.on("/s", []() {
        currentMode = MANUAL;
        stopMotors();
        server.send(200, "text/plain", "Stopped");
    });
    server.on("/l", []() {
        currentMode = MANUAL;
        Left();
        server.send(200, "text/plain", "Turning Left");
    });
    server.on("/r", []() {
        currentMode = MANUAL;
        Right();
        server.send(200, "text/plain", "Turning Right");
    });

    // Autonomous Mode endpoints
    server.on("/horn", handleSpecialMode);
    server.on("/track", handleSpecialMode);
    server.on("/avoid", handleSpecialMode);
    server.on("/follow", handleSpecialMode);

    server.begin();
    Serial.println("Server started!");
}

void loop()
{
    server.handleClient();

    if (currentMode == OBSTACLE)
    {
        obstacleMode();
    }
    else if (currentMode == FOLLOW)
    {
        followMode();
    }
    
    yield();
}

// Motor Movement Functions
void stopMotors()
{
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    setLeft(0);
    setRight(0);
    Serial.print("stop");
}

void forward()
{
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    setLeft(baseSpeed);
    setRight(baseSpeed);
    Serial.print("forward");
}

void backward()
{
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    setLeft(baseSpeed);
    setRight(baseSpeed);
    Serial.print("back");
}

void Left()
{
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    setLeft(baseSpeed);
    setRight(baseSpeed);
    Serial.print("left");
}

void Right()
{
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    setLeft(baseSpeed);
    setRight(baseSpeed);
    Serial.print("right");
}