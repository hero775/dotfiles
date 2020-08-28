/*
* File  : TB-I2C.c:
* version : 1.0
* Date : 2019. 5. 20.
* Author : TK Lee
* Contact : expoeb2@diwell.com
* Corporation : Diwell Electronics
*
* description :
*   TB-I2C example program to read the temperature.
*   (using wiringPi Library)
*
* Further information:
*   https://projects.drogon.net/raspberry-pi/wiringpi/
*   https://www.diwellshop.com/
*
* license : free.
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY.
***********************************************************************
* Note:
*   Raspberry Pi 2 Model B v1.1 used for testing.
*   This program has not been tested on other versions of the Raspberry.
***********************************************************************
* Revision history.
* 1. 2019.5.20 : First version is released.
***********************************************************************
*/


#include <stdint.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "wiringPi.h"
#include "wiringPiI2C.h"

#define SLAVE_Address 0x3A

int main(void)
{
	int rtc, i;
	int rawTemp[2];
	
	float SensorTemp, ObjTemp;

	wiringPiSetup();				// Wiring Pi setup

	delay(1000);					// Waiting for sensor initialization

 	if((rtc = wiringPiI2CSetup(SLAVE_Address)) == -1)	// Slave Adr = 0x3A
	{
		fprintf(stderr, "Unable to initialise I2C : %s\n",strerror (errno));
		return 1;
	}

	while(1){
		for(i=0; i<2; i++){
			rawTemp[i] = wiringPiI2CReadReg16(rtc,0x06+i);
			delay(1); 			//Don't delete this line
		}
		SensorTemp = (float)rawTemp[0]*0.02-273.15;
		ObjTemp = (float)rawTemp[1]*0.02-273.15;

		printf("SenT:%3.2f, ObjT:%3.2f\n", SensorTemp, ObjTemp);
		delay(500);
	}
	return 0;
}