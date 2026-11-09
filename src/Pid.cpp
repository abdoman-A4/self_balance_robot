#include "Pid.h"

namespace pid {
  // التعريف مرة واحدة هنا (كان معرَّفاً في Pid.h فظهر خطأ الرمز المكرر)
  PID myPID = {10.0, 0.001, 6.0, 0.0, 0.0};

  // أقصى قيمة للتكامل حتى لا ينفجر عند بقاء الروبوت مائلاً على الأرض
  const float INTEGRAL_LIMIT = 100.0;

    float calculatePID(float setpoint,
                         float measuredValue,
                         float dt) {
    
        if (dt <= 0.0) {
            return 0.0;
        }
    
        float error = setpoint - measuredValue;
    
        myPID.integral += error * dt;
        myPID.integral = constrain(myPID.integral, -INTEGRAL_LIMIT, INTEGRAL_LIMIT);
    
        float derivative =
            (error - myPID.previousError) / dt;
    
        myPID.previousError = error;
    
        return myPID.Kp * error
             + myPID.Ki * myPID.integral
             + myPID.Kd * derivative;
    }
}
