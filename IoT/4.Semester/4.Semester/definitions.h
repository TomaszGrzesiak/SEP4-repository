/*
 * definitions.h
 *
 * Created: 08/12/2022 05.54.42
 *  Author: Gabriel, Tomasz
 */ 

#ifndef DEFINITIONS_H_
#define DEFINITIONS_H_

#include <stdio.h>
#include <avr/io.h>

#include <ATMEGA_FreeRTOS.h>
#include <task.h>
#include <semphr.h>

#include <stdio_driver.h>
#include <serial.h>


// need for MessageBufferHandle
#include <lora_driver.h>


typedef struct programData{
	int16_t temperature; // int16 is from -32000 to + 32000
	uint16_t humidity; // uint16 is from 0 65000. CIRKA :)
	uint16_t CO2level;
	uint16_t light;
		
	uint16_t minCO2Setting;
	uint16_t maxCO2Setting;
	uint16_t minHumiditySetting;
	uint16_t maxHumiditySetting;
	int16_t minTemperatureSetting;
	int16_t maxTemperatureSetting;
	uint16_t minLightSetting;
	uint16_t maxLightSetting;
	}programData;
	
	programData data;
	
	SemaphoreHandle_t xSemaphore;
	MessageBufferHandle_t downLinkMessageBufferHandle;
	
#endif