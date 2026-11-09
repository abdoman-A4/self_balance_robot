
#include "gyro.h"
namespace gyro {
  MPU6050 mpu(Wire);

 
void GyroInit() {
  Serial.begin(9600); // سرعة Serial مناسبة للأونو
  Wire.begin();
  
  mpu.begin();
  
  Serial.println("جارِ معايرة الجيرسكوب... ثبت الروبوت ولا تحركه!");
  delay(1000);
  
  mpu.calcGyroOffsets(true); // معايرة تلقائية لإلغاء الانحراف
  Serial.println("تمت المعايرة بنجاح!");
}
void GyroStatePrint(){
  mpu.update();

  // طباعة زاوية الميل (عادة بتكون زاوية Pitch أو Roll حسب اتجاه تركيب الحساس)
  Serial.print("Angle X : ");
  Serial.print(mpu.getAngleX());
  Serial.print("\tAngle Y : ");
  Serial.println(mpu.getAngleY());

}
float GyroXStateRecord(){
  mpu.update();
  Serial.print("Angle X : ");
  Serial.println(mpu.getAngleX());
 return mpu.getAngleX();
}

}