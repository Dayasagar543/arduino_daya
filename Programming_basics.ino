// C++ code

// global variables
// variables

// constants which cannot be modifed in the program once you assign the values these will be marked as read only values
// these constant values can be used in the operations
const int run = 5;

// constant qualifiers
// #define would help in replaceing the values like constants use only if there is a shortage of meomery best
// practice is to use const variables  we also call them constant qualifiers..
#define pi 3.14

// booean
bool check = true;

// int
int myvariable = 5;
// byte<--- should be only used when it doesnot exceed 255 value
byte val = 121;
// char character='a';
char character = val;
// void setup
void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(9600);
    // printing the float values
    float floatval = 3.142;
    Serial.print("the float value is ");
    Serial.println(floatval);
}
// void loop
void loop()
{
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000); // Wait for 1000 millisecond(s)
    digitalWrite(LED_BUILTIN, LOW);
    delay(1000); // Wait for 1000 millisecond(s)
    // static qualifiers ----->are used to in side the functions where the value should not be reintialized again but also
    // value should not be a global variable
    // int value_loop=0;
    static int value_loop = 0;
    value_loop++;
    Serial.println(value_loop);

    // local variable
    int myvariable_2 = myvariable + 5;
    // 6
    Serial.println(++myvariable); // pre increment we also have post increment
    // 10
    Serial.println(myvariable_2);
    // 5
    Serial.println(--myvariable); // pre decrement we also have pre increment
    // 20
    Serial.println(myvariable_2 * 2);
    // 5
    Serial.println(myvariable_2 / 2);
    // 1
    Serial.println(myvariable_2 % 2);
    // boolean test
    Serial.print("checking the boolean variable  ");
    Serial.println(check);
    // printing the byte data
    Serial.print("priniting the byte variable ");
    Serial.println(val);
    // printing the character
    Serial.print("printing the character is  ");
    Serial.println(character);
    // printing the constant values
    Serial.print("printing the constant vlaue ");
    Serial.println(run);
    Serial.print("going to print the operation using const value ");
    Serial.println(run * 5);
    Serial.print("printing the cirle are using the #define variables ");
    Serial.println(pi * 5 * 5);
}