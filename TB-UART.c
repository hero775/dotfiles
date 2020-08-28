/*
 * File  : TB-UART.c:
 * version : 1.0
 * Date : 2019. 5. 20.
 * Author : TK Lee
 * Contact : expoeb2@diwell.com 
 * Corporation : Diwell Electronics
 *
 * description : 
 *   TB-UART example program to read the temperature.  
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

#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <wiringPi.h>
#include <wiringSerial.h>
typedef unsigned char	uint8_t;
typedef unsigned short	uint16_t; 
typedef unsigned int	uint32_t;
typedef int		int32_t;

#define MAX_BUFFER 8

uint16_t RX_BUF[MAX_BUFFER], rx_count;
uint8_t Checksum_cal(uint8_t CNT) ;

int main ()
{	
	uint8_t *ptr, response_flag=0;
	uint8_t TX_BUF[4]={0x11, 0x03, 0x01, 0x98};
	int32_t fd ;
	int32_t count ;
	int32_t Object, Sensor;
	uint32_t DelayMax = 100; // 100ms : Don't change this value.
	uint32_t Start_ms, request_count=0;
 
	if ((fd = serialOpen ("/dev/ttyAMA0", 19200)) < 0)
	{
		fprintf (stderr, "Unable to open serial device: %s\n", strerror (errno)) ;
		return 1 ;
	}

	if (wiringPiSetup () == -1)
	{
		fprintf (stdout, "Unable to start wiringPi: %s\n", strerror (errno)) ;
		return 1 ;
	}

	delay(200);                   // waiting for Sensor init.

	while(request_count++ < 100)  // repeat 100 times.
  	{
    	fflush (stdout) ;
		ptr = TX_BUF;
		response_flag = 0;
		for(count=0; count<4; count++)
		{
			serialPutchar (fd, *ptr++) ; 
		}

		Start_ms = millis();
		while( millis()-Start_ms < DelayMax ) 	// 100ms timer
    		{   
      			while (serialDataAvail (fd))
      			{ 
				RX_BUF[rx_count] = serialGetchar (fd);
      
				switch(rx_count)
      				{
				case 0:
					if(RX_BUF[0] == 0x16){rx_count++;}
					break;
				case 1:
					if(RX_BUF[1] == 0x04){rx_count++;}
					else{rx_count=0;}
					break;
				case 2 ... 6:
					rx_count++;
					break;
				case 7:
					if(RX_BUF[7] == 0x9C)
					{
						if(Checksum_cal(MAX_BUFFER) == RX_BUF[MAX_BUFFER -2])
						{
							Object = RX_BUF[2]<<8 | RX_BUF[3];
							Sensor = RX_BUF[4]<<8 | RX_BUF[5];
							if(Object > 40000){ Object -= 0x10000;}
							if(Sensor > 40000){ Sensor -= 0x10000;}
							printf ("%4d- Object: %3.2f  Sensor: %3.2f\n", request_count,(float)Object/100, (float)Sensor/100) ;
							response_flag = 1;
						}
						else
						{
							printf ("%4d- Checksum Fail.\n", request_count) ;
							response_flag = 2;
						}
      
					}
  					rx_count=0;   
					break;
				default: rx_count=0; break;

      				} // end switch(rx_count)
			} //end while (serialDataAvail (fd))
   		} // end while( millis()-Start_ms < DelayMax )	
   		if(response_flag==0)
   		{
   			printf("%4d-No response. Check the line(rx,tx)\n", request_count);
   		}
 	}
 	printf ("================Stopped================\n") ;
  	return 0 ;
}

uint8_t Checksum_cal(uint8_t CNT)    // CHECKSUM 
{
  uint8_t count, SUM=0;
  for(count=0; count<CNT-2; count++)
  {
     SUM += RX_BUF[count];
  }
  return SUM;
}

