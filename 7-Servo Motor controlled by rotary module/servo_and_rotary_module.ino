#include <Servo.h>

Servo myServo;

int clkPin = 2;       // Encoder CLK
int dtPin = 3;        // Encoder DT
int servoPin = 9;     // Servo signal pin

int lastClkState;
int angle = 90;       // Start in middle (range: 0–180)

void setup() {
  pinMode(clkPin, INPUT);
  pinMode(dtPin, INPUT);
  myServo.attach(servoPin);
  myServo.write(angle);

  lastClkState = digitalRead(clkPin);
}

void loop() {
  int clkState = digitalRead(clkPin);
  if (clkState != lastClkState && clkState == LOW) {
    // If the CLK changed, check direction
    if (digitalRead(dtPin) != clkState) {
      angle+=4;  // CW
    } else {
      angle-=4;  // CCW
    }

    // Limit angle between 0 and 180
    angle = constrain(angle, 0, 180);
    myServo.write(angle);
    delay(5);  // Slight debounce delay
  }
  lastClkState = clkState;
}
