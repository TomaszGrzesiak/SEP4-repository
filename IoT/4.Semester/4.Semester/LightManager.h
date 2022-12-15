/*
 * LightManager.h
 *
 * Created: 08/12/2022 13:36:33
 *  Author: Rodrigo Valente
 */ 

#include "tsl2591.h"
#include <stdint.h>

typedef struct lightSensor
{
	union
	{
		uint32_t lux;
		uint16_t visibleRaw;
		uint16_t infraredRaw;
		uint16_t fullSpectrum;
		};
}lightSensor;

typedef struct lightSensor* lightSensor_t;
lightSensor_t self;

lightSensor_t lightSensor_init();   

void lightMeasure(lightSensor_t self);  

void tsl2591Callback(tsl2591_returnCode_t returnCode, lightSensor_t self)

uint32_t getLux(lightSensor_t self);   
uint16_t getVisibleRaw(lightSensor_t self);   
uint16_t getInfraredRaw(lightSensor_t self);  
uint16_t getFullSpectrum(lightSensor_t self); 

void lightSensorTask(void* pvParameters);