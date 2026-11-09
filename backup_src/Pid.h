
#ifndef PID_H
#define PID_H

#include <Arduino.h>
#include <Wire.h>
#include <MPU6050_tockn.h>

namespace pid {
  struct PID {
    float Kp;
    float Ki;
    float Kd;
    float previousError;
    float integral;
  };

  PID myPID = {10.0, 0.001, 6.0, 0.0, 0.0};

  float calculatePID(float setpoint,
                     float measuredValue,
                     float dt);
}

#endif