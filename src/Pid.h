
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

  // تعريف واحد فقط في Pid.cpp. كتابته هنا تسبّب خطأ الرمز المكرر.
  extern PID myPID;

  float calculatePID(float setpoint,
                     float measuredValue,
                     float dt);
}

#endif