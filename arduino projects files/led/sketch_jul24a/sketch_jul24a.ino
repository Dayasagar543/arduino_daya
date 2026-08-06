const int ledpin= 13;
void setup(){
pinMode(ledpin,OUTPUT);
}
void blinkLED(int delayTime){
digitalWrite(ledpin,HIGH);
delay(delayTime);
digitalWrite(ledpin,LOW);
delay(delayTime);
}
void loop(){
  blinkLED(500);
}






