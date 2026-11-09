#ifndef PID_H
#define PID_H

#include <Arduino.h>

namespace pid {

struct PID {
  float Kp;
  float Ki;
  float Kd;

  float integral;
  float lastMeasurement;

  float outMin;
  float outMax;

  // Limits for the integral part, expressed in output units (PWM).
  // This is what keeps the integral from "winding up" when the robot is
  // lying on the floor.
  float iTermMin;
  float iTermMax;

  bool firstSample;

  void reset();

  // Derivative taken from the change of the measurement.
  float compute(float setpoint, float measured, float dt);

  // Derivative taken from an external rate signal (the gyro).
  // Preferred for balancing: smoother and free of angle-filter lag.
  float computeWithRate(float setpoint, float measured, float rate, float dt);
};

// The one global controller, defined in Pid.cpp.
extern PID balancePID;

void PidInit();

// Backwards compatible wrapper around balancePID.compute().
float calculatePID(float setpoint, float measuredValue, float dt);

} // namespace pid

#endif
