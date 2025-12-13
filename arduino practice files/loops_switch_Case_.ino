// C++ code
//
void setup()
{
    Serial.begin(9600);
    Serial.println("printing the  for code ");
    for (int i = 0; i < 10; i++)
    {
        if (i % 2 == 0)
        {
            Serial.println(i);
        }
        else
        {
            continue;
        }
    }

    Serial.println("printing the  while code ");
    int i = 0;
    while (i < 10)
    {
        Serial.println(i);
        i++;
        if (i == 5)
        {
            break;
        }
    }

    Serial.println("printing the do while code ");
    int j = 0;
    do
    {

        Serial.println(j);
        j++;
    } while (j <= 10);
    Serial.println("please enter number of the day 1-sunday");

    // serial data reading
    Serial.available();
    char data_input = Serial.read();
    Serial.println(data_input);
    // int day = 2;
    int day = 1;
    switch (day)
    {
    case 1:
        Serial.println("sunday");
        break;
    case 2:
        Serial.println("Monday");
        break;
    case 3:
        Serial.println("Tuesday");
        break;
    case 4:
        Serial.println("Wednesday");
        break;
    case 5:
        Serial.println("Thursday");
        break;
    case 6:
        Serial.println("Friday");
        break;
    case 7:
        Serial.println("Saturday");
        break;
    default:
        Serial.println("not a valid argument ");
        break;
    }
}

void loop()
{
    // for(int i=0;i<10;i++){
    // if(i%2==0){
    //  Serial.println(i);}
    // else{
    // continue;
    // return;
    //}
    //}
}