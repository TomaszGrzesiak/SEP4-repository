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
#include "Servo_emulator.h"
#include <rc_servo.h>

static servoEmulator_t servoEmulatorVentilator;

mh_z19_returnCode_t rc;

void performCO2Measuring_task(void *pvParameters);
static uint16_t calculateVentilatorPosition();
static uint16_t calculateBagActuatorPosition();


void myCo2CallBack(uint16_t ppm)
{
	data.CO2level = ppm;
}

void initializeCO2Manager() {
	// The parameter is the USART port the MH-Z19 sensor is connected to - in this case USART3
	mh_z19_initialise(ser_USART3);
	mh_z19_injectCallBack(myCo2CallBack);
	
	rc_servo_initialise();
	servoEmulatorVentilator = servoEmulator_create("Vent", 0, -100);

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
		servoEmulatorSetPosition(servoEmulatorVentilator, calculateVentilatorPosition());			
		
		rc_servo_setPosition(0, calculateBagActuatorPosition());
		vTaskDelay(pdMS_TO_TICKS(3000));
	}
}

static uint16_t calculateVentilatorPosition() {
	if (data.CO2level < data.maxCO2Setting) return 0; // ventilator shall remain closed, because the current level is below the maximum threshold. <- the mushroom farm does not need any fresh air. The CO2 level is not too high.
	return (100*(data.CO2level-data.maxCO2Setting)/data.CO2level);
}

static uint16_t calculateBagActuatorPosition() {
	if (data.CO2level > data.minCO2Setting) return 0; // the CO2 bag shall remain closed, because the current level is higher the minimum threshold. <- the mushroom farm does not need any extra CO2.
	return (100*(data.minCO2Setting-data.CO2level)/data.minCO2Setting);
}