int ledPin = 13;     // Built-in LED on pin 13
int pirPin = 12;     // PIR sensor connected to pin 12
int buzzerPin = 8;   // Active buzzer connected to pin 8
int pirValue;        // Variable to store PIR sensor value

void setup() {
  pinMode(ledPin, OUTPUT);     // Set LED pin as output
  pinMode(pirPin, INPUT);      // Set PIR pin as input
  pinMode(buzzerPin, OUTPUT);  // Set buzzer pin as output

  digitalWrite(ledPin, LOW);   // Turn off LED
  digitalWrite(buzzerPin, LOW); // Turn off buzzer
}

void loop() {
  pirValue = digitalRead(pirPin); // Read PIR sensor value

  digitalWrite(ledPin, pirValue);   // Mirror motion state to LED
  digitalWrite(buzzerPin, pirValue); // Activate buzzer on motion
}
