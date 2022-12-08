/*
 * CO2Manager.c
 *
 * Created: 30-11-2022 00:02:15
 *  Author: Tomasz Grzesiak
 */ 
#include "CO2Manager.h"
// including CO2 driver header
#include <mh_z19.h>
#include <stdio.h>
#include "definitions.h"

mh_z19_returnCode_t rc;

void myCo2CallBack(uint16_t ppm)
{
	printf("Callback CO2 Sensor readings: %d\n",ppm);
	data.CO2level = ppm;
}

void initializeCO2Manager() {
	// The parameter is the USART port the MH-Z19 sensor is connected to - in this case USART3
	mh_z19_initialise(ser_USART3);
	mh_z19_injectCallBack(myCo2CallBack);
}

void performCO2Measuring() {
	rc = mh_z19_takeMeassuring();
	if (rc != MHZ19_OK)
	{
		printf("CO2 Sensor readings: something went wrong.\n");
	}
	else
	{
		printf("CO2 Sensor readings: %d\n",data.CO2level);
	}
}

