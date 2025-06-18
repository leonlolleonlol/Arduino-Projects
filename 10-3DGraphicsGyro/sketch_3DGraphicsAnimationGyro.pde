import processing.serial.*;

Serial myPort;

float roll, pitch, yaw, accMag;
float smoothRoll = 0, smoothPitch = 0, smoothYaw = 0, smoothAcc = 0;
float smoothingFactor = 0.1;

void setup() {
  size(600, 600, P3D);
  println(Serial.list());
  myPort = new Serial(this, Serial.list()[0], 115200);
  myPort.bufferUntil('\n');
}

void draw() {
  background(200);
  lights();
  
  perspective(PI/3.0, width/(float)height, 1, 10000);
  camera(width/2, height/2, 500, width/2, height/2, 0, 0, 1, 0);
  
  translate(width/2, height/2, 0);

  // Use smooth angles directly without clamping
  rotateX(radians(smoothPitch));
  rotateZ(radians(smoothRoll));
  rotateY(radians(smoothYaw));

  float safeAcc = constrain(smoothAcc, 0.8, 1.5);
  float prismSize = map(safeAcc, 0.8, 1.5, 50, 300);
  prismSize = max(prismSize, 30);

  fill(100, 150, 250);
  stroke(0);
  box(prismSize, prismSize/2, prismSize/3);
}



 void serialEvent(Serial port) {
  String data = port.readStringUntil('\n');
  if (data != null) {
    data = trim(data);
    String[] tokens = split(data, ',');
    if (tokens.length == 4) {
      try {
        float r = Float.parseFloat(tokens[0]);
        float p = Float.parseFloat(tokens[1]);
        float y = Float.parseFloat(tokens[2]);
        float a = Float.parseFloat(tokens[3]);

        if (!Float.isNaN(r) && !Float.isNaN(p) && !Float.isNaN(y) && !Float.isNaN(a)) {
          smoothRoll = smoothingFactor * r + (1 - smoothingFactor) * smoothRoll;
          smoothPitch = smoothingFactor * p + (1 - smoothingFactor) * smoothPitch;
          smoothYaw = smoothingFactor * y + (1 - smoothingFactor) * smoothYaw;
          smoothAcc = smoothingFactor * a + (1 - smoothingFactor) * smoothAcc;
        } else {
          println("Warning: NaN received, ignoring this data line.");
        }
      } 
      catch (NumberFormatException e) {
        println("Warning: Could not parse float from serial data: " + data);
      }
    }
  }
}
