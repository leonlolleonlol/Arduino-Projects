#include <IRremote.hpp>

#define IR_RECEIVE_PIN 2      // IR receiver pin
#define MOTOR_PWM_PIN 3       // Motor control pin (to transistor base via resistor)

bool motorOn = false;
int motorSpeed = 255;         // Default speed (max)

// Define IR remote button codes (you'll need to update these based on your remote)
#define IR_CODE_POWER  0xBA45FF00
#define IR_CODE_0      0xE916FF00
#define IR_CODE_1      0xF30CFF00
#define IR_CODE_2      0xE718FF00
#define IR_CODE_3      0xA15EFF00
#define IR_CODE_4      0xF708FF00
#define IR_CODE_5      0xE31CFF00
#define IR_CODE_6      0xA55AFF00
#define IR_CODE_7      0xBD42FF00
#define IR_CODE_8      0xAD52FF00
#define IR_CODE_9      0xB54AFF00


void setup() {
  Serial.begin(115200);
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
  pinMode(MOTOR_PWM_PIN, OUTPUT);
  analogWrite(MOTOR_PWM_PIN, 0); // Start with motor off
}

unsigned long lastValidTime = 0;
const unsigned long debounceDelay = 200; // 200ms debounce delay

void loop() {
  if (IrReceiver.decode()) {
    unsigned long now = millis();
    unsigned long irCode = IrReceiver.decodedIRData.decodedRawData;

    // Filter out repeat or noise codes
    if (irCode == 0 || irCode == 0xFFFFFFFF) {
      IrReceiver.resume();
      return;
    }

    // Debounce: avoid reacting to rapid multiple triggers
    if (now - lastValidTime < debounceDelay) {
      IrReceiver.resume();
      return;
    }
    lastValidTime = now;

    Serial.print("Received code: ");
    Serial.println(irCode, HEX);

    // Handle IR codes
    switch (irCode) {
      case IR_CODE_POWER:
        motorOn = !motorOn;
        Serial.println(motorOn ? "Motor ON" : "Motor OFF");
        break;

      case IR_CODE_0: setSpeed(0); break;
      case IR_CODE_1: setSpeed(1); break;
      case IR_CODE_2: setSpeed(2); break;
      case IR_CODE_3: setSpeed(3); break;
      case IR_CODE_4: setSpeed(4); break;
      case IR_CODE_5: setSpeed(5); break;
      case IR_CODE_6: setSpeed(6); break;
      case IR_CODE_7: setSpeed(7); break;
      case IR_CODE_8: setSpeed(8); break;
      case IR_CODE_9: setSpeed(9); break;
    }

    // Update motor state
    if (motorOn) {
      analogWrite(MOTOR_PWM_PIN, motorSpeed);
    } else {
      analogWrite(MOTOR_PWM_PIN, 0); // Motor off
    }

    IrReceiver.resume(); // Ready for next signal
  }
}


// Map digit (0–9) to PWM value (50–255)
void setSpeed(int digit) {
  if (digit < 0 || digit > 9) return;

  // Map 0–9 to speed range 50–255
  motorSpeed = map(digit, 0, 9, 50, 255);
  Serial.print("Speed set to: ");
  Serial.println(motorSpeed);
}
