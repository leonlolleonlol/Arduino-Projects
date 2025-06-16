#include <LedControl.h>

// Pins for MAX7219
LedControl lc = LedControl(11, 13, 10, 1);

// Joystick pins
const int xPin = A0;
const int yPin = A1;

// Snake body (max 64 segments)
int snakeX[64];
int snakeY[64];
int snakeLength = 3;

// Direction: 0=up, 1=right, 2=down, 3=left
int dir = 1;

// Apple position
int appleX, appleY;

void setup() {
  lc.shutdown(0, false);
  lc.setIntensity(0, 1);
  lc.clearDisplay(0);

  // Initial snake position
  snakeX[0] = 3; snakeY[0] = 3;
  snakeX[1] = 2; snakeY[1] = 3;
  snakeX[2] = 1; snakeY[2] = 3;

  placeApple();
}

void loop() {
  readJoystick();

  moveSnake();

  if (checkCollision()) {
    gameOver();
    return;
  }

  if (snakeX[0] == appleX && snakeY[0] == appleY) {
    snakeLength++;
    placeApple();
  }

  draw();
  delay(400);
}

void readJoystick() {
  int xVal = analogRead(xPin);
  int yVal = analogRead(yPin);

  if (xVal < 400 && dir != 1) dir = 3; // left
  else if (xVal > 600 && dir != 3) dir = 1; // right
  else if (yVal < 400 && dir != 2) dir = 0; // up
  else if (yVal > 600 && dir != 0) dir = 2; // down
}

void moveSnake() {
  // Shift body
  for (int i = snakeLength - 1; i > 0; i--) {
    snakeX[i] = snakeX[i - 1];
    snakeY[i] = snakeY[i - 1];
  }

  // Move head
  if (dir == 0) snakeY[0]--;
  if (dir == 1) snakeX[0]++;
  if (dir == 2) snakeY[0]++;
  if (dir == 3) snakeX[0]--;
}

bool checkCollision() {
  // Wall collision
  if (snakeX[0] < 0 || snakeX[0] > 7 || snakeY[0] < 0 || snakeY[0] > 7)
    return true;

  // Self collision
  for (int i = 1; i < snakeLength; i++) {
    if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i])
      return true;
  }

  return false;
}

void placeApple() {
  bool valid;
  do {
    valid = true;
    appleX = random(0, 8);
    appleY = random(0, 8);

    for (int i = 0; i < snakeLength; i++) {
      if (snakeX[i] == appleX && snakeY[i] == appleY) {
        valid = false;
        break;
      }
    }
  } while (!valid);
}

void draw() {
  lc.clearDisplay(0);

  // Draw snake
  for (int i = 0; i < snakeLength; i++) {
    lc.setLed(0, snakeY[i], snakeX[i], true);
  }

  // Draw apple
  lc.setLed(0, appleY, appleX, true);
}

void gameOver() {
  // Flash all LEDs
  for (int i = 0; i < 3; i++) {
    lc.clearDisplay(0);
    delay(200);
    for (int row = 0; row < 8; row++) {
      for (int col = 0; col < 8; col++) {
        lc.setLed(0, row, col, true);
      }
    }
    delay(200);
  }

  // Reset game
  snakeLength = 3;
  snakeX[0] = 3; snakeY[0] = 3;
  snakeX[1] = 2; snakeY[1] = 3;
  snakeX[2] = 1; snakeY[2] = 3;
  dir = 1;
  placeApple();
}
