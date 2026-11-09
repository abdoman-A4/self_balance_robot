#include "gyro.h"

namespace gyro {

namespace {

MPU6050 mpu(Wire);

float lastAngle = 0.0f;
float lastRate  = 0.0f;

unsigned long lastPrintMs = 0;

} // namespace

void GyroInit() {
  Wire.begin();
  // 400 kHz I2C: the sensor read takes ~0.3 ms instead of ~1.3 ms.
  // If the board ever fails to detect the MPU6050, comment this line out.
  Wire.setClock(400000);

  mpu.begin();

  Serial.println(F("Calibrating gyro - do NOT move the robot..."));
  // console = true, wait 1 s before, 0.5 s after the calibration.
  mpu.calcGyroOffsets(true, 1000, 500);
  Serial.println(F("Gyro calibrated."));

  // Prime the complementary filter so the first reading is valid.
  GyroUpdate();
  lastPrintMs = millis();
}

void GyroUpdate() {
  mpu.update();
  lastAngle = mpu.getAngleX();
  lastRate  = mpu.getGyroX();
}

float GyroXStateRecord() {
  return lastAngle;
}

float GyroXRate() {
  return lastRate;
}

void GyroStatePrint(unsigned long periodMs) {
  unsigned long now = millis();
  if (now - lastPrintMs < periodMs) {
    return;
  }
  lastPrintMs = now;

  Serial.print(F("angleX="));
  Serial.print(lastAngle, 2);
  Serial.print(F("\trateX="));
  Serial.print(lastRate, 2);
  Serial.println();
}

} // namespace gyro
