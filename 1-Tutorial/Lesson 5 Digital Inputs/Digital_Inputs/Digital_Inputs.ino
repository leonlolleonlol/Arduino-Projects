//www.elegoo.com
//2016.12.08

int ledPin = 5;
int buttonApin = 9;
int value = 0;

byte leds = 0;

void setup() 
{
  pinMode(ledPin, OUTPUT);
  pinMode(buttonApin, INPUT_PULLUP);  
}

void loop() 
{
  if (digitalRead(buttonApin) == LOW) {
    value = 1 - value;               // Toggle value
    digitalWrite(ledPin, value);     // Update LED
    delay(100);                      // Debounce delay
    while (digitalRead(buttonApin) == LOW);  // Wait until button is released
  }
}
