//www.elegoo.com
//2016.12.8

// Define Pins
#define BLUE 3
#define GREEN 5
#define RED 6

void setup()
{
pinMode(RED, OUTPUT);
pinMode(GREEN, OUTPUT);
pinMode(BLUE, OUTPUT);
digitalWrite(RED, LOW);
digitalWrite(GREEN, LOW);
digitalWrite(BLUE, LOW);
}

// define variables
int redValue;
int greenValue;
int blueValue;

// main loop
void loop()
{}
/*
#define delayTime 2500 // fading time between colors
//#define maxIntensity 255

redValue = random(0, 256); // choose a value between 1 and 255 to change the color.
greenValue = random(0, 256);
blueValue = random(0, 256);
analogWrite(RED, redValue);
analogWrite(GREEN, greenValue);
analogWrite(BLUE, blueValue);
delay(delayTime);
}*/

