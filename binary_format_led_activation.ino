// C++ code
int value=15;
int led1=5,led2=6,led3=7,led4=8;
void setup()
{
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  Serial.begin(9600);
  
  for(int i=0;i<=value;i++){
	binary_converter(i);
 }
}

void loop()
{
  
}

void binary_converter(int number){
  int binary_value=0;
  int place=1,i=0;
  int array[4]={};
  while(number>0){
  int remainder=number%2;
   binary_value=binary_value+remainder*place;
   place*=10;
   number=number/2;
  }
  Serial.println(binary_value);
  delay(1000);
  while(binary_value>0){
    array[i]=binary_value%10;
    binary_value=binary_value/10;
    i++;
  }
  delay(1000);
  for(int i=0;i<=4;i++){
  digitalWrite(i+5,array[i]);
  }
  delay(1000);
}

