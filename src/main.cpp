#include <Arduino.h>

#include "gyro.h"
#include "motor.h"
#include "Pid.h"

using namespace gyro;
using namespace motor;
using namespace pid;

/* ============================== TUNING =================================== */

// Angle (degrees) at which the robot is perfectly balanced.
// Hold the robot upright and read `angle=` on the Serial Monitor to find it.
const float SETPOINT = -70.0f;

// PID gains (output is in PWM units, -255..255).
//   Kp : how strongly it reacts to tilt.    Too low -> falls over.
//                                           Too high -> fast oscillation.
//   Ki : leave at 0.0 for a pure balance loop. A tiny value can remove a
//        permanent lean, but it also makes the robot slowly drive away.
//   Kd : damping, acts on the gyro rate.    Too low -> wobbles/overshoots.
//                                           Too high -> buzzes and shakes.
const float KP = 18.0f;
const float KI = 0.0f;
const float KD = 0.8f;

// Safety: if the robot leans further than this from SETPOINT, cut the motors.
const float FALL_LIMIT_DEG = 35.0f;

// After a fall the robot must be held within this angle, for this long,
// before the motors are allowed to run again.
const float REARM_LIMIT_DEG = 12.0f;
const unsigned long REARM_HOLD_MS = 400;

// Control loop period: 10 ms -> 100 Hz. Matches the MPU6050_tockn filter,
// which measures its own dt with millis().
const unsigned long SAMPLE_PERIOD_US = 10000;

// Telemetry period.
const unsigned long LOG_PERIOD_MS = 100;

/* ========================================================================= */

unsigned long previousMicros = 0;
unsigned long rearmStartMs = 0;
bool armed = false;

void setup() {
  Serial.begin(115200);
  delay(200);
  Serial.println(F("Self-balancing robot starting..."));

  GyroInit();
  MotorInit();

  balancePID.Kp = KP;
  balancePID.Ki = KI;
  balancePID.Kd = KD;
  balancePID.outMin = -255.0f;
  balancePID.outMax = 255.0f;
  balancePID.iTermMin = -40.0f;
  balancePID.iTermMax = 40.0f;
  PidInit();

  previousMicros = micros();
  rearmStartMs = millis();

  Serial.println(F("Hold the robot upright to arm it."));
}

void loop() {
  const unsigned long now = micros();
  if (now - previousMicros < SAMPLE_PERIOD_US) {
    return;
  }

  float dt = (now - previousMicros) / 1000000.0f;
  previousMicros = now;

  // If the loop was ever blocked (Serial, I2C glitch), do not let a huge dt
  // create a huge derivative spike.
  if (dt > 0.05f) {
    dt = 0.05f;
  }

  GyroUpdate();
  const float angle = GyroXStateRecord();
  const float rate = GyroXRate();

  // ---------------------------- Safety -----------------------------------
  const bool fallen =
      isnan(angle) || isnan(rate) || fabsf(angle - SETPOINT) > FALL_LIMIT_DEG;

  if (fallen) {
    if (armed) {
      MotorStop();
      armed = false;
    }
    balancePID.reset();
    rearmStartMs = millis();
  } else if (!armed) {
    // Re-arm only after the robot has been held near the balance point for a
    // while, so it cannot suddenly take off while lying on the floor.
    if (fabsf(angle - SETPOINT) <= REARM_LIMIT_DEG) {
      if (millis() - rearmStartMs >= REARM_HOLD_MS) {
        balancePID.reset();
        armed = true;
      }
    } else {
      rearmStartMs = millis();
    }
  }

  // --------------------------- Controller --------------------------------
  int output = 0;
  if (armed) {
    output = (int)balancePID.computeWithRate(SETPOINT, angle, rate, dt);
    MotorDrive(output);
  }

  // ---------------------------- Telemetry --------------------------------
  static unsigned long lastLogMs = 0;
  if (millis() - lastLogMs >= LOG_PERIOD_MS) {
    lastLogMs = millis();

    Serial.print(armed ? F("RUN ") : F("IDLE"));
    Serial.print(F("\tangle="));
    Serial.print(angle, 2);
    Serial.print(F("\trate="));
    Serial.print(rate, 1);
    Serial.print(F("\tout="));
    Serial.println(output);
  }
}
