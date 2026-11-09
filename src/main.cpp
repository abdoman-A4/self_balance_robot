// #include <Arduino.h>
// #include <Wire.h>
// #include <MPU6050_tockn.h>

// //LIBRARYS
// #include "gyro.h"
// #include "motor.h"
// using namespace gyro;
// using namespace motor;

// //========================

// //PID control variables
// struct PID {
//   float Kp; // Proportional gain
//   float Ki; // Integral gain
//   float Kd; // Derivative gain
//   float previousError; // Previous error value
//   float integral; // Integral of the error
// };
// PID myPID = {1.0, 0.0, 0.0, 0.0, 0.0}; // Initialize PID parameters
// //========================


// // void setup() {
// //   GyroInit(); // استدعاء دالة تهيئة الجيروسكوب                           
// //   MotorInit(); // استدعاء دالة تهيئة الموتور
// // }

// // void loop() {
// //  //GyroStatePrint(); // استدعاء دالة طباعة حالة الجيروسكوب
// //   // delay(500); // تأخير نصف ثانية قبل التحديث التالي
// //   MotorForward(150); // تشغيل الموتور للأمام بسرعة 150
// //   delay(2000); // تشغيل الموتور للأمام لمدة ثانيتين
// //   MotorBackward(150); // تشغيل الموتور للخلف بسرعة 150
// //   delay(2000); // تشغيل الموتور للخلف لمدة ثانيتين
// //   calculatePID(-70.0, GyroXStateRecord(), 0.01); // حساب قيمة PID بناءً على زاوية الجيروسكوب
// // }
// //==========================
// //TEST
// float setpoint = -70.0;

// unsigned long previousMicros = 0;
// const unsigned long sampleTime = 10000; // 10 ms

// void setup() {
//     Serial.begin(9600);

//     GyroInit();
//     MotorInit();

//   float calculatePID(float setpoint,
//                    float measuredValue,
//                    float dt);

//     previousMicros = micros();
// }

// void loop() {
//     unsigned long now = micros();

//     if (now - previousMicros < sampleTime) {
//         return;
//     }

//     float dt = (now - previousMicros) / 1000000.0;
//     previousMicros = now;

//     float angle = GyroXStateRecord();

//     // حد أمان تجريبي: أوقف الدفع إذا مال الروبوت كثيرًا
//     if (abs(angle) > 30.0) {
//         MotorStop();
//         myPID.integral = 0;
//         myPID.previousError = 0;
//         return;
//     }

//     float output = calculatePID(setpoint, angle, dt);

//     // حصر الخرج لأغراض الاختبار الأولي
//     output = constrain(output, -100, 100);

//     int motorSpeed = (int)abs(output);

//     if (output > 0) {
//         MotorForward(motorSpeed);
//     } 
//     else if (output < 0) {
//         MotorBackward(motorSpeed);
//     } 
//     else {
//         MotorStop();
//     }

//     Serial.print("Angle: ");
//     Serial.print(angle);
//     Serial.print(" | PID: ");
//     Serial.println(output);
// }

// //==========================
// //  PID control loop for self-balancing robot (not implemented yet)

// // int calculatePID(float setpoint, float measuredValue) {
// //   float error = setpoint - measuredValue;
// //   myPID.integral += error;
// //   float derivative = error - myPID.previousError;
// //   myPID.previousError = error;
// //   return myPID.Kp * error + myPID.Ki * myPID.integral + myPID.Kd * derivative;
// // }

// float calculatePID(float setpoint,
//                    float measuredValue,
//                    float dt) {

//     float error = setpoint - measuredValue;

//     myPID.integral += error * dt;

//     float derivative =
//         (error - myPID.previousError) / dt;

//     myPID.previousError = error;

//     float output =
//         myPID.Kp * error
//         + myPID.Ki * myPID.integral
//         + myPID.Kd * derivative;

//     return output;
// }


//gpt hbd

// #include <Arduino.h>
// #include <Wire.h>
// #include <MPU6050_tockn.h>

// #include "gyro.h"
// #include "motor.h"

// using namespace gyro;
// using namespace motor;

// struct PID {
//     float Kp;
//     float Ki;
//     float Kd;
//     float previousError;
//     float integral;
// };

// PID myPID = {10.0, 0.001, 6.0, 0.0, 0.0};

// float calculatePID(float setpoint,
//                    float measuredValue,
//                    float dt);

// float setpoint = -70.0;

// unsigned long previousMicros = 0;
// const unsigned long sampleTime = 10000;

// void setup() {
//     Serial.begin(9600);

//     GyroInit();
//     MotorInit();

//     previousMicros = micros();
// }

// void loop() {
//     unsigned long now = micros();

//     if (now - previousMicros < sampleTime) {
//         return;
//     }

//     float dt = (now - previousMicros) / 1000000.0;
//     previousMicros = now;

//     float angle = GyroXStateRecord();

//     if (angle > -30.0 || angle < -130.0) {
//         MotorStop();
//         myPID.integral = 0;
//         myPID.previousError = 0;
//         return;
        
//     }

//     float output = calculatePID(setpoint, angle, dt);
//     output = constrain(output, -100.0, 100.0);

//     int motorSpeed =(int)fabs(output);

//     if (output < setpoint) {
//         MotorForward(motorSpeed);
//     } else if (output > setpoint) {
//         MotorBackward(motorSpeed);
//     } else {
//         MotorStop();
//     }

//     Serial.print("Angle: ");
//     Serial.print(angle);
//     Serial.print(" | PID: ");
//     Serial.println(output);
// }

// float calculatePID(float setpoint,
//                    float measuredValue,
//                    float dt) {

//     if (dt <= 0.0) {
//         return 0.0;
//     }

//     float error = setpoint - measuredValue;

//     myPID.integral += error * dt;

//     float derivative =
//         (error - myPID.previousError) / dt;

//     myPID.previousError = error;

//     return myPID.Kp * error
//          + myPID.Ki * myPID.integral
//          + myPID.Kd * derivative;
// }


#include <Arduino.h>
#include <Wire.h>
#include <MPU6050_tockn.h>

#include "gyro.h"
#include "motor.h"
#include "Pid.h"
using namespace gyro;
using namespace motor;
using namespace pid;

float setpoint = -70.0;

unsigned long previousMicros = 0;
const unsigned long sampleTime = 10000;

// حدود الأمان
const float fallLimitDeg = 35.0;       // إذا مال أكثر من هذا نوقف الموتورات
const float rearmLimitDeg = 12.0;      // يجب أن يعود داخل هذه الزاوية...
const unsigned long rearmHoldMs = 400; // ...ويبقى فيها هذه المدة قبل التشغيل

bool armed = false;
unsigned long rearmStartMs = 0;

void setup() {
    Serial.begin(115200);

    GyroInit();
    MotorInit();

    previousMicros = micros();
    rearmStartMs = millis();
}

void loop() {
    unsigned long now = micros();

    if (now - previousMicros < sampleTime) {
        return;
    }

    float dt = (now - previousMicros) / 1000000.0;
    previousMicros = now;

    // حماية من قفزة كبيرة في dt إذا تأخرت الحلقة
    if (dt > 0.05) {
        dt = 0.05;
    }

    float angle = GyroXStateRecord();

    float output = 0.0;

    // فحص السقوط: أوقف الموتورات إذا خرج عن زاوية الأمان
    if (fabs(angle - setpoint) > fallLimitDeg) {
        MotorStop();
        myPID.integral = 0;
        myPID.previousError = 0;
        armed = false;
        rearmStartMs = millis();
    } else {
        // لا تعمل الموتورات حتى يُثبَّت الروبوت قريباً من نقطة التوازن
        if (!armed) {
            if (fabs(angle - setpoint) <= rearmLimitDeg) {
                if (millis() - rearmStartMs >= rearmHoldMs) {
                    myPID.integral = 0;
                    myPID.previousError = 0;
                    armed = true;
                }
            } else {
                rearmStartMs = millis();
            }
        }

        if (armed) {
            output = calculatePID(setpoint, angle, dt);

            // المدى الكامل للموتور 0..255
            output = constrain(output, -255.0, 255.0);

            // الاتجاه من إشارة الخرج نفسها (وليس بمقارنته بـ setpoint)
            if (output > 0) {
                MotorForward((int)output);
            } else if (output < 0) {
                MotorBackward((int)(-output));
            } else {
                MotorStop();
            }
        }
    }

    // طباعة الحالة كل 100 مللي ثانية فقط (الطباعة كل دورة تبطئ التحكم)
    static unsigned long lastPrint = 0;
    if (millis() - lastPrint >= 100) {
        lastPrint = millis();

        Serial.print(armed ? "RUN  " : "IDLE ");
        Serial.print("Angle: ");
        Serial.print(angle);
        Serial.print(" | Output: ");
        Serial.println(output);
    }
}