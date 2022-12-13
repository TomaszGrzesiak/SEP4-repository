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

void performCO2Measuring_task(void *pvParameters);

void myCo2CallBack(uint16_t ppm)
{
	data.CO2level = ppm;
}

void initializeCO2Manager() {
	// The parameter is the USART port the MH-Z19 sensor is connected to - in this case USART3
	mh_z19_initialise(ser_USART3);
	mh_z19_injectCallBack(myCo2CallBack);
	xTaskCreate(
	performCO2Measuring_task
	,  "measuring CO2 and putting data into data struct in definitions.h"  // A name just for humans
	,  configMINIMAL_STACK_SIZE  // This stack size can be checked & adjusted by reading the Stack Highwater
	,  NULL
	,  0  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
	,  NULL );
	

}

void performCO2Measuring_task(void *pvParameters) {
	for (;;) {
		rc = mh_z19_takeMeassuring();
		if (rc != MHZ19_OK)
		{
			printf("CO2 Sensor readings: something went wrong.\n");
		}
		else
		{
			printf("CO2 Sensor readings: %d\n",data.CO2level);
		}
		vTaskDelay(pdMS_TO_TICKS(3000));
	}
}

