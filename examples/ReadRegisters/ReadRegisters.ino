/*
    Basic Example 3.

    SCA100T -library allows communication with Murata SCA100T inclinometer sensors using SPI.

    This sketch shows the basic usage of the sensor interface. 
    Program reads sensor register values in raw values. 
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
  Serial.println(F("Starting example 3 - Read register values"));
}

void loop() 
{
  Serial.print(F("Register RWTR value is: "));
  registerValue = mySensor.readRaw(SCA_TEMP); // Temperature register value
  Serial.println(byte(registerValue));

  Serial.print(F("Register RDAX value is: "));
  registerValue = mySensor.readRaw(SCA_ACCEL_X); // X-axis acceleration register value
  Serial.println(registerValue);
  
  Serial.print(F("Register RDAY value is: "));
  registerValue = mySensor.readRaw(SCA_ACCEL_Y); // Y-axis acceleration register value
  Serial.println(registerValue);
  
  delay(1000);
}
