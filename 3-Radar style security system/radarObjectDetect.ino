// Stepper pins
#define STEPPER_PIN_1 9
#define STEPPER_PIN_2 10
#define STEPPER_PIN_3 11
#define STEPPER_PIN_4 12

// Ultrasonic sensor pins
const int trigPin = 7;
const int echoPin = 8;

// LED pins
const int redPin = 2;
const int yellowPin = 4;
const int greenPin = 5;

// Radar variables
int step_number = 0;
int angle = 0;
int direction = 1;
int steps_per_degree = 3;
int steps_taken = 0;

void setup() {
  // Stepper setup
  pinMode(STEPPER_PIN_1, OUTPUT);
  pinMode(STEPPER_PIN_2, OUTPUT);
  pinMode(STEPPER_PIN_3, OUTPUT);
  pinMode(STEPPER_PIN_4, OUTPUT);

  // Ultrasonic setup
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // LED setup
  pinMode(redPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(greenPin, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  OneStep(direction);
  delay(5);
  steps_taken++;

  if (steps_taken >= steps_per_degree) {
    steps_taken = 0;

    long duration = getPulseDuration();
    long cm = microsecondsToCentimeters(duration);

    // LED control based on distance
    digitalWrite(redPin, cm <= 5);
    digitalWrite(yellowPin, cm > 5 && cm <= 15);
    digitalWrite(greenPin, cm > 15);

    // Send data to Processing
    Serial.print(angle);
    Serial.print(",");
    Serial.println(cm);

    if (direction == 1) angle++;
    else angle--;

    if (angle >= 180) {
      angle = 180;
      direction = 0;
    } else if (angle <= 0) {
      angle = 0;
      direction = 1;
    }
  }
}

void OneStep(bool dir) {
  if (dir) {
    switch (step_number) {
      case 0: digitalWrite(STEPPER_PIN_1, HIGH); digitalWrite(STEPPER_PIN_2, LOW); digitalWrite(STEPPER_PIN_3, LOW); digitalWrite(STEPPER_PIN_4, LOW); break;
      case 1: digitalWrite(STEPPER_PIN_1, LOW); digitalWrite(STEPPER_PIN_2, HIGH); digitalWrite(STEPPER_PIN_3, LOW); digitalWrite(STEPPER_PIN_4, LOW); break;
      case 2: digitalWrite(STEPPER_PIN_1, LOW); digitalWrite(STEPPER_PIN_2, LOW); digitalWrite(STEPPER_PIN_3, HIGH); digitalWrite(STEPPER_PIN_4, LOW); break;
      case 3: digitalWrite(STEPPER_PIN_1, LOW); digitalWrite(STEPPER_PIN_2, LOW); digitalWrite(STEPPER_PIN_3, LOW); digitalWrite(STEPPER_PIN_4, HIGH); break;
    }
  } else {
    switch (step_number) {
      case 0: digitalWrite(STEPPER_PIN_1, LOW); digitalWrite(STEPPER_PIN_2, LOW); digitalWrite(STEPPER_PIN_3, LOW); digitalWrite(STEPPER_PIN_4, HIGH); break;
      case 1: digitalWrite(STEPPER_PIN_1, LOW); digitalWrite(STEPPER_PIN_2, LOW); digitalWrite(STEPPER_PIN_3, HIGH); digitalWrite(STEPPER_PIN_4, LOW); break;
      case 2: digitalWrite(STEPPER_PIN_1, LOW); digitalWrite(STEPPER_PIN_2, HIGH); digitalWrite(STEPPER_PIN_3, LOW); digitalWrite(STEPPER_PIN_4, LOW); break;
      case 3: digitalWrite(STEPPER_PIN_1, HIGH); digitalWrite(STEPPER_PIN_2, LOW); digitalWrite(STEPPER_PIN_3, LOW); digitalWrite(STEPPER_PIN_4, LOW); break;
    }
  }
  step_number++;
  if (step_number > 3) step_number = 0;
}

long getPulseDuration() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  return pulseIn(echoPin, HIGH);
}

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}
