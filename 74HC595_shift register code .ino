int latch_pin = 11;
int data_pin = 12;
int clock_pin = 9;
int dt = 1000;
// byte leds=0xFF;
// byte leds0 = 0b00000000;
byte leds0 = 0b11111111;
byte leds1 = 0b10101010;
byte leds2 = 0b01010101;

void setup()
{
    // put your setup code here, to run once:
    pinMode(latch_pin, OUTPUT);
    pinMode(data_pin, OUTPUT);
    pinMode(clock_pin, OUTPUT);
    Serial.begin(9600);
}

void loop()
{
    // put your main code here, to run repeatedly :
    delay(dt);
    digitalWrite(latch_pin, LOW);
    shiftOut(data_pin, clock_pin, LSBFIRST, leds0);
    // right shifting bits
    leds0 = leds0 >> 1;
    // leds0=leds0/2;
    Serial.println(leds0, BIN);
    // left shifting bits
    //  leds0=leds0 << 1;
    digitalWrite(latch_pin, HIGH);
    // leds0 = leds0 + 1;

    //   delay(dt);
    //   digitalWrite(latch_pin, LOW);
    //   shiftOut(data_pin, clock_pin, LSBFIRST,leds1 );
    //   digitalWrite(latch_pin, HIGH);
    //   delay(dt);
    //   digitalWrite(latch_pin, LOW);
    //   shiftOut(data_pin, clock_pin, LSBFIRST, leds2);
    //   digitalWrite(latch_pin, HIGH);
}

// for(byte i=0;i<=255;i++){
// digitalWrite(latch_pin,LOW);
//  shiftOut(data_pin,clock_pin,LSBFIRST,i);
// digitalWrite(latch_pin,HIGH);
// delay(dt);
// }
