// #pragma once
#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>
struct Motor {
    int forwardPin;
    int backwardPin;
    int enablePin;
  int speed;
};

// إعلان (Declaration) المتغيرات فقط باستخدام extern لعدم تكرار حجز الذاكرة
extern Motor motor1;
extern Motor motor2;

namespace motor {
  void MotorInit();
  void MotorForward(int speed);
  void MotorBackward(int speed);
  void MotorStop();
}

#endif