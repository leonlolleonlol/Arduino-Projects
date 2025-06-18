#include <Wire.h>
#include <MPU6050_tockn.h>

MPU6050 mpu(Wire);

#define FILTER_SIZE 5

float rollBuffer[FILTER_SIZE] = {0};
float pitchBuffer[FILTER_SIZE] = {0};
float yawBuffer[FILTER_SIZE] = {0};
float accBuffer[FILTER_SIZE] = {0};
int filterIndex = 0;

float avgRoll = 0, avgPitch = 0, avgYaw = 0, avgAcc = 0;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  mpu.begin();
  mpu.calcGyroOffsets(true);
}

void loop() {
  mpu.update();

  float roll = mpu.getAccAngleX();
  float pitch = mpu.getAccAngleY();
  float yaw = mpu.getGyroZ();

  float ax = mpu.getAccX();
  float ay = mpu.getAccY();
  float az = mpu.getAccZ();
  float accMagnitude = sqrt(ax*ax + ay*ay + az*az);

  rollBuffer[filterIndex] = roll;
  pitchBuffer[filterIndex] = pitch;
  yawBuffer[filterIndex] = yaw;
  accBuffer[filterIndex] = accMagnitude;

  filterIndex++;
  if(filterIndex >= FILTER_SIZE) filterIndex = 0;

  avgRoll = 0; avgPitch = 0; avgYaw = 0; avgAcc = 0;
  for(int i=0; i<FILTER_SIZE; i++) {
    avgRoll += rollBuffer[i];
    avgPitch += pitchBuffer[i];
    avgYaw += yawBuffer[i];
    avgAcc += accBuffer[i];
  }
  avgRoll /= FILTER_SIZE;
  avgPitch /= FILTER_SIZE;
  avgYaw /= FILTER_SIZE;
  avgAcc /= FILTER_SIZE;

  Serial.print(avgRoll); Serial.print(",");
  Serial.print(avgPitch); Serial.print(",");
  Serial.print(avgYaw); Serial.print(",");
  Serial.println(avgAcc);

  delay(20);
}
