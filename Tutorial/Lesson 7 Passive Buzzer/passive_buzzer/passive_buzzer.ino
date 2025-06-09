//www.elegoo.com
//2016.12.08

#include "pitches.h"
 
int melody[] = {
  392, 392, 440, 392, 349, 330, 392, 392,
  440, 392, 349, 330, 294, 294, 330, 349,
  392, 392, 330, 294, 330, 349, 392
};

int noteDurations[] = {
  500, 500, 500, 500, 500, 500, 500, 500,
  500, 500, 500, 500, 500, 500, 500, 500,
  500, 500, 500, 500, 500, 500, 1000
};

int buzzerPin = 8;

void setup() {
  for (int i = 0; i < sizeof(melody) / sizeof(melody[0]); i++) {
    int noteDuration = noteDurations[i];
    int note = melody[i];

    if (note > 0) {
      tone(buzzerPin, note, noteDuration);
    }

    delay(noteDuration * 1.3);
    noTone(buzzerPin);
  }
}

void loop() {
  // Nothing to repeat
}
