/*
 * TemperatureHumdity.h
 *
 * Created: 08/12/2022 04.40.12
 *  Author: gabri
 */ 

#include <stdio.h>
#include <avr/io.h>

#include <ATMEGA_FreeRTOS.h>
#include <task.h>
#include <semphr.h>

#include <stdio_driver.h>
#include <serial.h>
#include "hih8120.h"
#include "definitions.h"


void temperatureHumiditySensorTask(void* pvParameters);