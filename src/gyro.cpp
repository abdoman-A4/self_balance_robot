
#include "gyro.h"
namespace gyro {
  MPU6050 mpu(Wire);

 
void GyroInit() {
  Serial.begin(115200); // سرعة عالية حتى لا تتأخر حلقة التحكم
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
  // قراءة واحدة فقط وبدون طباعة:
  // الطباعة هنا كانت تحجب الحلقة ~26 مللي ثانية وتسبب سقوط الروبوت
  mpu.update();
  return mpu.getAngleX();
}

}
