/*
 * definitions.h
 *
 * Created: 08/12/2022 05.54.42
 *  Author: gabri
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

typedef struct programData{
	int16_t temperature;
	uint16_t humidity;
	}programData;
	
	programData data;
	
	SemaphoreHandle_t xSemaphore;
	
#endif