/*
    Basic Example 4.

    SCA100T -library allows communication with Murata SCA100T inclinometer sensors using SPI.

    This sketch shows the basic usage of the sensor interface. 
    Program puts the device in self test mode and reads the test-result. 
*/

#include <SCA100T.h>
int chipSelect = 10;
long spiBusSpeed = 500000;
int sensorType = SCA100TD02;

SCA100T mySensor(chipSelect,spiBusSpeed,SCA100TD02);

int registerValue = 0;

void setup() 
{
  Serial.begin(115200);
  Serial.println(F("Starting example 4 - Self test."));
}

void loop() 
{
  int i=10;
  // Start self test on X-axis
  mySensor.startSelfTest(SCA_ACCEL_X);
  Serial.print(F("Self test started on X-axis, reading values: "));
  while(i--)
  {
    Serial.println(mySensor.readRaw(SCA_ACCEL_X));
    delay(100);
  }
  mySensor.stopSelfTest();

  // Start self test on Y-axis
  mySensor.startSelfTest(SCA_ACCEL_Y);
  Serial.print(F("Self test started on Y-axis, reading values: "));
  i = 10;
  while(i--)
  {
    Serial.println(mySensor.readRaw(SCA_ACCEL_Y));
    delay(100);
  }
  mySensor.stopSelfTest();
  
  delay(1000);
}
