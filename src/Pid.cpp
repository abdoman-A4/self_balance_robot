#include "Pid.h"

namespace pid {

// Default gains. main.cpp overwrites them from its TUNING block, so tune
// there, not here.
PID balancePID = {
    18.0f,   // Kp
    0.0f,    // Ki
    0.8f,    // Kd
    0.0f,    // integral
    0.0f,    // lastMeasurement
    -255.0f, // outMin
    255.0f,  // outMax
    -40.0f,  // iTermMin
    40.0f,   // iTermMax
    true     // firstSample
};

void PID::reset() {
  integral = 0.0f;
  lastMeasurement = 0.0f;
  firstSample = true;
}

float PID::computeWithRate(float setpoint, float measured, float rate, float dt) {
  if (dt <= 0.0f) {
    return 0.0f;
  }
  if (isnan(measured) || isnan(rate)) {
    return 0.0f;
  }

  if (firstSample) {
    // Ignore the derivative on the very first sample: there is nothing to
    // differentiate against yet.
    firstSample = false;
    integral = 0.0f;
  }

  const float error = setpoint - measured;
  const float pTerm = Kp * error;

  // error = setpoint - measured, so d(error)/dt = -d(measured)/dt = -rate.
  const float dTerm = -Kd * rate;

  float iTerm = 0.0f;
  if (Ki != 0.0f) {
    integral += error * dt;
    iTerm = Ki * integral;

    // Anti-windup: clamp the integral contribution, not the raw sum.
    if (iTerm > iTermMax) {
      iTerm = iTermMax;
      integral = iTerm / Ki;
    } else if (iTerm < iTermMin) {
      iTerm = iTermMin;
      integral = iTerm / Ki;
    }
  }

  float output = pTerm + iTerm + dTerm;

  if (output > outMax) {
    output = outMax;
  } else if (output < outMin) {
    output = outMin;
  }

  return output;
}

float PID::compute(float setpoint, float measured, float dt) {
  if (dt <= 0.0f) {
    return 0.0f;
  }

  float rate = 0.0f;
  if (!firstSample) {
    rate = (measured - lastMeasurement) / dt;
  }
  lastMeasurement = measured;

  return computeWithRate(setpoint, measured, rate, dt);
}

void PidInit() {
  balancePID.reset();
}

float calculatePID(float setpoint, float measuredValue, float dt) {
  return balancePID.compute(setpoint, measuredValue, dt);
}

} // namespace pid
