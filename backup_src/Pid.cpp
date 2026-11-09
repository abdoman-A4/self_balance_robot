#include "Pid.h"

namespace pid {
  PID myPID = {10.0, 0.001, 6.0, 0.0, 0.0};

    float calculatePID(float setpoint,
                         float measuredValue,
                         float dt) {
    
        if (dt <= 0.0) {
            return 0.0;
        }
    
        float error = setpoint - measuredValue;
    
        myPID.integral += error * dt;
    
        float derivative =
            (error - myPID.previousError) / dt;
    
        myPID.previousError = error;
    
        return myPID.Kp * error
             + myPID.Ki * myPID.integral
             + myPID.Kd * derivative;
    }
    //
    
    float output = calculatePID(setpoint, angle, dt);
    output = constrain(output, -100.0, 100.0);

    int motorSpeed =(int)fabs(output);

    if (output < setpoint) {
        MotorForward(motorSpeed);
    } else if (output > setpoint) {
        MotorBackward(motorSpeed);
    } else {
        MotorStop();
    }

    Serial.print("Angle: ");
    Serial.print(angle);
    Serial.print(" | PID: ");
    Serial.println(output);
}

float calculatePID(float setpoint,
                   float measuredValue,
                   float dt) {

    if (dt <= 0.0) {
        return 0.0;
    }

    float error = setpoint - measuredValue;

    myPID.integral += error * dt;

    float derivative =
        (error - myPID.previousError) / dt;

    myPID.previousError = error;

    return myPID.Kp * error
         + myPID.Ki * myPID.integral
         + myPID.Kd * derivative;
}