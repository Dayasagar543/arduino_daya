const int ledpin=5;
void setup(){
pinMode(ledpin,OUTPUT);
}

void loop(){
  blinkLED(5000);
}


void blinkLED(int delayTime){
digitalWrite(ledpin,HIGH);
delay(delayTime);
digitalWrite(ledpin,LOW);
delay(delayTime);
}



