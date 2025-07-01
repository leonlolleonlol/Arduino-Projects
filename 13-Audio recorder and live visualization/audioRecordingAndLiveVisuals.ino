#include <LedControl.h>

LedControl lc = LedControl(51, 52, 10, 1); // DIN, CLK, CS

const int soundPin = A0;
const int numCols = 8;
int barHeights[numCols];

void setup() {
  lc.shutdown(0, false);
  lc.setIntensity(0, 8);
  lc.clearDisplay(0);
  Serial.begin(9600);
}

void loop() {
  int raw = analogRead(soundPin);
  Serial.print("Raw: ");
  Serial.println(raw);

  int baseline = 519;
  int amplitude = abs(raw - baseline);

  // Amplify the sensitivity by mapping smaller amplitude to taller height
  int sensitivityThreshold = 3;  // minimum amplitude to consider as sound
int maxAmplitude = 25;         // louder sounds should map to full height

int height = 0;
if (amplitude > sensitivityThreshold) {
  height = map(amplitude, sensitivityThreshold, maxAmplitude, 1, 8);
  height = constrain(height, 1, 8);
}


  // Shift bar history
  for (int i = 0; i < numCols - 1; i++) {
    barHeights[i] = barHeights[i + 1];
  }
  barHeights[numCols - 1] = height;

  drawCenteredBars();
  delay(50);
}

void drawCenteredBars() {
  lc.clearDisplay(0);

  for (int col = 0; col < numCols; col++) {
    int h = barHeights[col];

    // Always light the center rows
    lc.setLed(0, 3, col, true);
    lc.setLed(0, 4, col, true);

    int extra = h - 2;
    if (extra <= 0) continue;

    // Evenly split extra rows above and below
    int upper = extra / 2;
    int lower = extra - upper;

    // Draw lower rows: below row 3 → rows 2,1,0
    for (int i = 1; i <= lower; i++) {
      int row = 3 - i;
      if (row >= 0) lc.setLed(0, row, col, true);
    }

    // Draw upper rows: above row 4 → rows 5,6,7
    for (int i = 1; i <= upper; i++) {
      int row = 4 + i;
      if (row <= 7) lc.setLed(0, row, col, true);
    }
  }
}
