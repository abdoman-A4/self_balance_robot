#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

struct Motor {
  int forwardPin;
  int backwardPin;
  int enablePin;
};

// Defined once in motor.cpp, visible everywhere through these declarations.
extern Motor motor1;
extern Motor motor2;

namespace motor {

// Configures the pins and makes sure both motors are stopped.
void MotorInit();

// Raw commands: pwm is 0..255. "Forward" = the robot drives forward.
void MotorForward(int pwm);
void MotorBackward(int pwm);
void MotorStop();

// Signed command in -255..255, as produced by the PID.
// Handles the direction and the motor dead zone (low PWM does not turn
// the wheels, so small commands are boosted to a PWM that actually moves).
void MotorDrive(int output);

} // namespace motor

#endif
