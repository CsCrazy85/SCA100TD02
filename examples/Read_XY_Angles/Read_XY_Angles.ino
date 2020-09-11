#include <SCA100T.h>
int chipSelect = 10;
long spiBusSpeed = 500000;
int sensorType = SCA100TD02;

SCA100T mySensor(chipSelect,spiBusSpeed,SCA100TD02);

void setup() 
{
  Serial.begin(115200);
  Serial.println(F("Starting example 1 - Read X and Y -angles."));
}

void loop() 
{
  float angle_X = mySensor.getAngle(SCA_ACCEL_Y);
  float angle_Y = mySensor.getAngle(SCA_ACCEL_Y);
  Serial.print(F("Angle X: "));
  Serial.print(angle_X);
  Serial.print(F("Angle Y: "));
  Serial.print(angle_Y);
  delay(1000);
}
