
#include "motor.h"

int speed =150;// Variable to hold the speed value
Motor motor1 = {11, 10,9, speed}; // Motor 1 pins and speed
Motor motor2 = {6, 5,3, speed};   // Motor 2 pins


// int const motorFORWARD1= 11;
// int const motorBACKWARD1= 10;
// int const motorFORWARD2= 6;
// int const motorBACKWARD2= 5;


namespace motor {
  // تعريف دوال التحكم بالموتور هنا
  void MotorInit() {
    // تهيئة الموتور
    Serial.println("Motor initialized.");
    pinMode(motor1.enablePin, OUTPUT);
  pinMode(motor1.forwardPin, OUTPUT);
  pinMode(motor1.backwardPin, OUTPUT);
  pinMode(motor2.enablePin, OUTPUT);
  pinMode(motor2.forwardPin, OUTPUT);
  pinMode(motor2.backwardPin, OUTPUT);
  }

  int applyMinimumSpeed(int speed) {
    speed = constrain(speed, 0, 255);

    if (speed > 0 && speed < 70) {
        speed = 70;
    }

    return speed;
}
  

  void MotorForward(int speed) {
    // التحكم في سرعة الموتور
    speed = applyMinimumSpeed(speed);
    Serial.print("Motor speed set to: ");
    Serial.println(speed);
    analogWrite(motor1.enablePin, speed);
    analogWrite(motor2.enablePin, speed);
   digitalWrite(motor1.forwardPin, HIGH);
    digitalWrite(motor1.backwardPin, 0);
    digitalWrite(motor2.forwardPin, HIGH);
    digitalWrite(motor2.backwardPin, 0);
  }
  void MotorBackward(int speed) {
    // التحكم في سرعة الموتور
    speed = applyMinimumSpeed(speed);
    Serial.print("Motor speed set to: ");
    Serial.println(speed);
    analogWrite(motor1.enablePin, speed);
    analogWrite(motor2.enablePin, speed);
   digitalWrite(motor1.forwardPin, 0);
    digitalWrite(motor1.backwardPin, HIGH);
    digitalWrite(motor2.forwardPin, 0);
    digitalWrite(motor2.backwardPin, HIGH);
  }
  void MotorStop() {
    analogWrite(motor1.enablePin, 0);
    analogWrite(motor2.enablePin, 0);

    digitalWrite(motor1.forwardPin, LOW);
    digitalWrite(motor1.backwardPin, LOW);

    digitalWrite(motor2.forwardPin, LOW);
    digitalWrite(motor2.backwardPin, LOW);
}
}