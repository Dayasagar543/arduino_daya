int tilt_pin=4;
int red_led=10;
int blue_led=11;
void setup() {
  // put your setup code here, to run once:
 pinMode(tilt_pin,INPUT);
 pinMode(red_led,OUTPUT);
 pinMode(blue_led,OUTPUT);
 digitalWrite(tilt_pin,HIGH);
 Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
 int tilt_val=digitalRead(tilt_pin);
 Serial.println(tilt_val);
 if(tilt_val==1){
  digitalWrite(red_led,HIGH);
  digitalWrite(blue_led,LOW);
 }else{
  digitalWrite(blue_led,HIGH);
  digitalWrite(red_led,LOW);
 }
// digitalWrite(blue_led,LOW);
// digitalWrite(red_led,LOW);
}
