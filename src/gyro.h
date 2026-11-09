#ifndef GYRO_H
#define GYRO_H

#include <Arduino.h>
#include <Wire.h>
#include <MPU6050_tockn.h>

namespace gyro {

// Starts I2C, starts the MPU6050 and calibrates the gyro offsets.
// The robot MUST stand still during this call (~5 s).
// Call once in setup().
void GyroInit();

// Reads the sensor and updates the internal filter.
// Call exactly once per control cycle, before reading any value.
void GyroUpdate();

// Filtered tilt angle around the X axis, in degrees.
float GyroXStateRecord();

// Angular rate around the X axis, in degrees per second.
// Use this for the derivative term: it is much cleaner than
// differentiating the angle.
float GyroXRate();

// Prints angle and rate to Serial, at most once every `periodMs`.
void GyroStatePrint(unsigned long periodMs = 200);

} // namespace gyro

#endif
