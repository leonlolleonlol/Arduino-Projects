#include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {22, 23, 24, 25};
byte colPins[COLS] = {26, 27, 28, 29};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

int buzzerPin = 8;

String minutesStr = "";
String secondsStr = "";
bool enteringSeconds = false;
bool timerSet = false;

unsigned long endTime = 0;
unsigned long lastDisplayTime = 0;

void setup() {
  Serial.begin(9600);
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, LOW);
}

void loop() {
  char key = keypad.getKey();

  // Key handling
  if (key) {
    Serial.print("Key: ");
    Serial.println(key);

    if (!timerSet) {
      if (key == '*') {
        enteringSeconds = true;
      } else if (key == '#') {
        int mins = minutesStr.toInt();
        int secs = secondsStr.toInt();
        int totalSeconds = mins * 60 + secs;
        endTime = millis() + totalSeconds * 1000UL;
        Serial.print("Timer Set: ");
        Serial.print(mins);
        Serial.print(" min ");
        Serial.print(secs);
        Serial.println(" sec");
        timerSet = true;
        lastDisplayTime = millis();
      } else if (key >= '0' && key <= '9') {
        if (!enteringSeconds) {
          minutesStr += key;
        } else {
          secondsStr += key;
        }
        Serial.print("Entered Time: ");
        Serial.print(minutesStr);
        Serial.print(":");
        Serial.println(secondsStr);
      }
    } else {
      // Timer is running
      if (key == 'A') {
        Serial.println("Timer cancelled.");
        resetTimer();
      }
    }
  }

  // Countdown display and timer check
  if (timerSet) {
    unsigned long remainingMillis = endTime - millis();
    if ((long)remainingMillis <= 0) {
      Serial.println("Timer Done!");
      tone(buzzerPin, 1000);
      delay(1000);
      noTone(buzzerPin);
      resetTimer();
    } else if (millis() - lastDisplayTime >= 1000) {
      lastDisplayTime = millis();
      int remainingSec = remainingMillis / 1000;
      int displayMin = remainingSec / 60;
      int displaySec = remainingSec % 60;
      Serial.print("Time left: ");
      if (displayMin < 10) Serial.print("0");
      Serial.print(displayMin);
      Serial.print(":");
      if (displaySec < 10) Serial.print("0");
      Serial.println(displaySec);
    }
  }
}

void resetTimer() {
  minutesStr = "";
  secondsStr = "";
  enteringSeconds = false;
  timerSet = false;
}
