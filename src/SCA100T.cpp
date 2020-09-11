/*
	www.hutasu.net
	Mika Väyrynen 11.9.2020
	
	SCA100T.cpp - This small library allows communication with Murata SCA100T inclinometer sensors using SPI.
*/

#include <SCA100T.h>

SPISettings sensorSettings(500000,MSBFIRST,DATAMODE);

/*
	Constructor
*/
SCA100T::SCA100T(int csPin, unsigned long comSpeed, int sensorType)
{	
	this->_cs = csPin;
	this -> sensorType = sensorType;
	this -> _comSpeed = comSpeed;
	pinMode(_cs,OUTPUT);
	// start the SPI library:
	SPI.begin();
}

/*
	changeCommSpeed(long value)
	Change SPI-bus speed for the sensor. Upper limit is 500 kHz and the speed is set to closest value possible.
*/
void SCA100T::changeCommSpeed(long value)
{
	if(value <= SCA100T_MAXSPEED)
	{
		sensorSettings = SPISettings(value,MSBFIRST,DATAMODE);
		// This feature is tested and checked as working with an oscilloscope (11.9.2020)
	}
}

/*
	getTemperature()
	Reads the temperaturevalue in degrees C.
*/
float SCA100T::getTemperature()
{
	float celsius=0.0;
	word tempRaw = 0;
	tempRaw = this -> readRaw(SCA_TEMP);
	celsius = (((float)tempRaw - 197.0) / (-1.083));
	return celsius;
}

/*
	Reads the acceleration value from the sensor and calculates the angle
*/
float SCA100T::getAngle(int axis)
{
	float angle = 0.0;
	switch(axis)
	{
		case SCA_ACCEL_X:
			angle = (float)this->readRaw(SCA_ACCEL_X);
		break;
		case SCA_ACCEL_Y:
			angle = (float)this->readRaw(SCA_ACCEL_Y);
		break;
	}
	if(sensorType == SCA100TD02)
	{
		angle = ((float)angle-1024.0) / SCA100TD02_SENSITIVITY;
	}
	else
	{
		angle = ((float)angle-1024.0) / SCA100TD01_SENSITIVITY;
	}
	angle = asin(angle);
	// asin returns value in radians so it's necessary to convert them to degrees
	angle = angle * RADIAN_IN_DEGREES;
	if(angle > 90.0)
	{
		angle = 90.0;
	}
	return angle;
}
/*
	readRaw(int reg)
	Reads a raw bit-value from the registers. Only acceleration and temperature registers are available. 
*/
word SCA100T::readRaw(int reg)
{
	word regValue = 0;
	SPI.beginTransaction(sensorSettings);
	delayMicroseconds(150);
	switch(reg)
	{
		case  SCA_ACCEL_X:
			digitalWrite(_cs,LOW);
			SPI.transfer(CMD_RDAX);
			regValue = SPI.transfer(0);
			regValue <<= 8;
			regValue |= SPI.transfer(0);
			regValue >>= 5;
			digitalWrite(_cs,HIGH);
			if(regValue > ACCEL_MAX_VALUE)
			{
				regValue = ACCEL_MAX_VALUE;
			}
			break;
		case  SCA_ACCEL_Y:
			digitalWrite(_cs,LOW);
			SPI.transfer(CMD_RDAY);
			regValue = SPI.transfer(0);
			regValue <<= 8;
			regValue |= SPI.transfer(0);
			regValue >>= 5;
			digitalWrite(_cs,HIGH);
			if(regValue > ACCEL_MAX_VALUE)
			{
				regValue = ACCEL_MAX_VALUE;
			}
			break;
		case  SCA_TEMP:
			delayMicroseconds(150);
			digitalWrite(_cs,LOW);
			SPI.transfer(CMD_RWTR);
			regValue = SPI.transfer(0);
			digitalWrite(_cs,HIGH);
			break;
	}
	SPI.endTransaction();
	return regValue;
}
/*
	startSelfTest()
	Puts the sensor into self-test mode.
*/
void SCA100T::startSelfTest(int axis)
{
	if(axis == SCA_ACCEL_X)
	{
		this -> sendCMD(CMD_STX);
	}
	else if(axis == SCA_ACCEL_Y)
	{
		this -> sendCMD(CMD_STY);
	}
	else
	{
		// unknown command
	}
	
}
/*
	stopSelfTest()
	Stops the sensor self-test mode.
*/
void SCA100T::stopSelfTest()
{
	this -> sendCMD(0);
}
/*
	sendCMD(byte command)
	Sends command to the chip. Useful if you want to command the chip into self-test mode etc...
*/
void SCA100T::sendCMD(byte command)
{
	SPI.beginTransaction(sensorSettings);
	digitalWrite(_cs,LOW);
	SPI.transfer(command);
	digitalWrite(_cs,HIGH);
	SPI.endTransaction();
}

