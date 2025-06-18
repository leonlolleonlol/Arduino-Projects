import processing.serial.*;

Serial port;
float angle = 0;
float distance = 0;

void setup() {
  size(600, 600);
  port = new Serial(this, Serial.list()[0], 9600);
  port.bufferUntil('\n');
  smooth();
}

void draw() {
  background(0);
  translate(width/2, height);
  stroke(0, 255, 0);
  noFill();

  // Radar arcs
  for (int i = 1; i <= 5; i++) {
    arc(0, 0, i*50, i*50, PI, TWO_PI);
  }

  // Sweep line
  float a = radians(map(angle, 0, 180, 0, 180));
  float r = map(distance, 0, 200, 0, 250);  // adjust range

  float x = cos(a) * r;
  float y = -sin(a) * r;

  stroke(0, 255, 0);
  line(0, 0, x, y);
  fill(0, 255, 0);
  ellipse(x, y, 6, 6);
}

void serialEvent(Serial port) {
  String data = port.readStringUntil('\n');
  if (data != null) {
    data = trim(data);
    String[] parts = split(data, ",");
    if (parts.length == 2) {
      angle = float(parts[0]);
      distance = float(parts[1]);
    }
  }
}
