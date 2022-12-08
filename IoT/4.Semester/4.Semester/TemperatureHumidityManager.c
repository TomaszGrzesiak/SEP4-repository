/*
 * TemperatureHumidity.c
 *
 * Created: 08/12/2022 04.39.34
 *  Author: gabri
 */ 

#include <stdio.h>
#include <avr/io.h>

#include <ATMEGA_FreeRTOS.h>
#include <task.h>
#include <semphr.h>

#include <stdio_driver.h>
#include <serial.h>
#include "TemperatureHumidityManager.h"
#include "hih8120.h"
#include "definitions.h"


void temperatureHumiditySensorTask(void* pvParameters){
	
	
	while(1){
		vTaskDelay(1000);
		int r = hih8120_wakeup();
		if(r != HIH8120_OK && r != HIH8120_TWI_BUSY) {
			printf("temp-wake error: %d\n", r);
		}
		
		vTaskDelay(100);
		r = hih8120_measure();
		if(r != HIH8120_OK && r != HIH8120_TWI_BUSY) {
			printf("Temp-read error: %d\n", r);

		}
		vTaskDelay(100);
		printf("task 3 delay 1000");
		xSemaphoreTake(xSemaphore, portMAX_DELAY);
		data.humidity = hih8120_getHumidity();
		data.temperature = hih8120_getTemperature();
		printf("Hum: %d  Temp: %d\n", data.humidity, data.temperature);
		xSemaphoreGive(xSemaphore);
	}
}