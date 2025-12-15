int potention_meter=A1;
int data;
int dt=500;
void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  data=analogRead(potention_meter);
  Serial.println(data);
  delay(dt);

}