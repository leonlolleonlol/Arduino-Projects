#include "pitches.h"

const int buzzer = 8;  // Connect passive buzzer to pin 8

void setup() {
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600);
  Serial.println("Virtual Piano Ready. Type keys QWERTYUIOP or 1234567890-");
}

void loop() {
  if (Serial.available()) {
    char key = Serial.read();
    int note = getNoteFromKey(key);
    if (note > 0) {
      tone(buzzer, note);
      delay(300); // play duration
      noTone(buzzer);
    }
  }
}

// Map keyboard characters to frequencies
int getNoteFromKey(char key) {
  switch (key) {
    case 'q': return NOTE_C4;
    case 'w': return NOTE_D4;
    case 'e': return NOTE_E4;
    case 'r': return NOTE_F4;
    case 't': return NOTE_G4;
    case 'y': return NOTE_A4;
    case 'u': return NOTE_B4;
    case 'i': return NOTE_C5;
    case 'o': return NOTE_D5;
    case 'p': return NOTE_E5;

    // black keys (sharps)
    case '1': return NOTE_CS4;
    case '2': return NOTE_DS4;
    case '4': return NOTE_FS4;
    case '5': return NOTE_GS4;
    case '6': return NOTE_AS4;
    case '8': return NOTE_CS5;
    case '9': return NOTE_DS5;
    case '0': return NOTE_FS5;
    case '-': return NOTE_GS5;

    default: return 0;
  }
}
