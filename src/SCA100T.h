/*
	www.hutasu.net
	Mika Väyrynen 11.9.2020
	
	SCA100TD02.h- This small library allows communication with Murata SCA100T inclinometer sensors using SPI.
*/
#include <Arduino.h>

#ifndef _SCA100T_H_
#define _SCA100T_H_

#include <math.h>
#include <SPI.h>

#define CMD_MEAS        0b00000000    // Measure mode (normal operation mode after power on)
#define CMD_RWTR        0b00001000    // Read temperature data register
#define CMD_STX         0b00001110    // Activate Self test for X-channel
#define CMD_STY         0b00001111    // Activate Self test for Y-channel
#define CMD_RDAX        0b00010000    // Read X-channel acceleration
#define CMD_RDAY        0b00010001    // Read Y-channel acceleration

#define DATAMODE        		SPI_MODE3
#define SCA100T_MAXSPEED        500000

#define SCA_ANGLE		1
#define SCA_ACCEL_X		2
#define SCA_ACCEL_Y		3
#define SCA_TEMP		4

#define RADIAN_IN_DEGREES	57.2955		// 57.2957795
#define ACCEL_MAX_VALUE		2048

#define SCA100TD02		102
#define SCA100TD01		101

#define SCA100TD02_SENSITIVITY		819
#define SCA100TD01_SENSITIVITY		1638

class SCA100T
{
	public: 
		SCA100T(int csPin, unsigned long comSpeed, int sensorType);	// constructor
		void changeCommSpeed(long value);
		float getTemperature();
		float getAngle(int axis);
		word readRaw(int axis);
		void startSelfTest(int axis);
		void stopSelfTest();
		void sendCMD(byte command);
	private:
		int _cs;
		int sensorType = 0;
		int _comSpeed = 0;
		word rdax=0;
		word rday=0;
		word rwtr=0;

};

// ########################### COMPILER CHECKS (DO NOT TOUCH IF IN DOUBT) #########################################

// NONE

#endif