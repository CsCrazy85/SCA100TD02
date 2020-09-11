/*
    Basic Example 5.

    SCA100T -library allows communication with Murata SCA100T inclinometer sensors using SPI.

    This sketch shows the basic usage of the sensor interface. 
    Program changes the SPI-speed to lower speed and then back, while reading sensor data.
*/

#include <SCA100T.h>
int chipSelect = 10;
long spiBusSpeed = 500000;
int sensorType = SCA100TD02;

SCA100T mySensor(chipSelect,spiBusSpeed,SCA100TD02);

void setup() 
{
  Serial.begin(115200);
  Serial.println(F("Starting example 5 - Change SPI speed."));
}

void loop() 
{
  int i=10;
  while(i--)
  {
    Serial.println(F("Angle on X: "));
    Serial.println(mySensor.getAngle(SCA_ACCEL_X));
    Serial.println(F("Angle on Y: "));
    Serial.println(mySensor.getAngle(SCA_ACCEL_Y));
    if(i == 5)
    {
      Serial.println(F("Changing speed to 100 kHz!"));
      mySensor.changeCommSpeed(100000); // Should be about 125 kHz in reality
    }
    delay(1000);
  }
  Serial.println(F("Changing back to full speed!"));
  mySensor.changeCommSpeed(500000); // 500 kHz
  
  delay(1000);
}
