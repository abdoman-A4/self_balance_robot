#include "motor.h"

// ============================ MOTOR TUNING =================================
// If one wheel turns the wrong way, set its INVERT flag to true (or simply
// swap the two wires of that motor).
static const bool INVERT_MOTOR1 = false;
static const bool INVERT_MOTOR2 = false;

// Smallest PWM value that actually overcomes friction and turns the wheels.
// Too low  -> the robot ignores small corrections and drifts away.
// Too high -> the robot twitches around the balance point.
static const int MIN_PWM = 55;

// Controller outputs smaller than this are treated as "stop" so the motors
// do not buzz when the robot is almost balanced.
static const int STOP_BAND = 7;
// ===========================================================================

Motor motor1 = {11, 10, 9};
Motor motor2 = {6, 5, 3};

namespace {

// Drives one motor at `pwm` (0..255) in the requested direction.
void writeMotor(const Motor &m, int pwm, bool forward, bool invert) {
  pwm = constrain(pwm, 0, 255);
  if (invert) {
    forward = !forward;
  }

  analogWrite(m.enablePin, pwm);
  digitalWrite(m.forwardPin, forward ? HIGH : LOW);
  digitalWrite(m.backwardPin, forward ? LOW : HIGH);
}

// Cuts the power to one motor and lets it coast.
void coastMotor(const Motor &m) {
  analogWrite(m.enablePin, 0);
  digitalWrite(m.forwardPin, LOW);
  digitalWrite(m.backwardPin, LOW);
}

} // namespace

namespace motor {

void MotorInit() {
  pinMode(motor1.forwardPin, OUTPUT);
  pinMode(motor1.backwardPin, OUTPUT);
  pinMode(motor1.enablePin, OUTPUT);

  pinMode(motor2.forwardPin, OUTPUT);
  pinMode(motor2.backwardPin, OUTPUT);
  pinMode(motor2.enablePin, OUTPUT);

  MotorStop();
  Serial.println(F("Motors ready."));
}

void MotorStop() {
  coastMotor(motor1);
  coastMotor(motor2);
}

void MotorForward(int pwm) {
  writeMotor(motor1, pwm, true, INVERT_MOTOR1);
  writeMotor(motor2, pwm, true, INVERT_MOTOR2);
}

void MotorBackward(int pwm) {
  writeMotor(motor1, pwm, false, INVERT_MOTOR1);
  writeMotor(motor2, pwm, false, INVERT_MOTOR2);
}

void MotorDrive(int output) {
  if (output > 255) {
    output = 255;
  } else if (output < -255) {
    output = -255;
  }

  int magnitude = abs(output);

  if (magnitude < STOP_BAND) {
    MotorStop();
    return;
  }

  // Dead-zone compensation: jump to MIN_PWM instead of applying a PWM that
  // is too weak to move the robot.
  int pwm = (magnitude < MIN_PWM) ? MIN_PWM : magnitude;

  if (output > 0) {
    MotorForward(pwm);
  } else {
    MotorBackward(pwm);
  }
}

} // namespace motor
