// #pragma once
#ifndef GYRO_H
#define GYRO_H

#include <Arduino.h>
#include <Wire.h>
#include <MPU6050_tockn.h>

namespace gyro {
  void GyroInit();
  void GyroStatePrint();
  float GyroXStateRecord();
}

#endif