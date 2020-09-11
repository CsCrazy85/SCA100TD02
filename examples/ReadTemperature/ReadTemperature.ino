/*
    Basic Example 2.

    SCA100T -library allows communication with Murata SCA100T inclinometer sensors using SPI.

    This sketch shows the basic usage of the sensor interface. 
    Program reads the temperature from the sensor and displays it on a serial interface.
  
*/

#include <SCA100T.h>
int chipSelect = 10;
long spiBusSpeed = 500000;
int sensorType = SCA100TD02;

SCA100T mySensor(chipSelect,spiBusSpeed,SCA100TD02);

float temperature;
void setup() 
{
  Serial.begin(115200);
  Serial.println(F("Starting example 2 - Read temperature."));
}

void loop() 
{
  temperature = mySensor.getTemperature();
  Serial.print(F("Temperature is: "));
  Serial.println(temperature);
  delay(1000);
}
