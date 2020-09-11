/*
    Basic Example 1.

    SCA100T -library allows communication with Murata SCA100T inclinometer sensors using SPI.

    This sketch shows the basic usage of the sensor interface. 
    Program reads the angle from the sensor and prints it to a serial port.
  
*/

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
  float angle_X = mySensor.getAngle(SCA_ACCEL_X);
  float angle_Y = mySensor.getAngle(SCA_ACCEL_Y);
  Serial.print(F("Angle X: "));
  Serial.print(angle_X);
  Serial.print(F("Angle Y: "));
  Serial.print(angle_Y);
  delay(1000);
}
