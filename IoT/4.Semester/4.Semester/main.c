/*
* main.c
* Author : IHA
*
* Example main file including LoRaWAN setup
* Just for inspiration :)
*/

#include <stdio.h>
#include <avr/io.h>

#include <ATMEGA_FreeRTOS.h>
#include <task.h>
#include <semphr.h>

#include <stdio_driver.h>
#include <serial.h>

 // Needed for LoRaWAN
#include <lora_driver.h>
#include <status_leds.h>

#include "CO2Manager.h"
#include "definitions.h" // contains a semaphore and the current values from the sensors
#include "TemperatureHumidityManager.h"
#include <display_7seg.h> // 7-segment Display Driver. A real display on the IoT device (4 digits only)

// define two Tasks
void task1( void *pvParameters );
void task2( void *pvParameters );


// Prototype for LoRaWAN handler
void _handler_initialise(UBaseType_t _handler_task_priority);

/*-----------------------------------------------------------*/
void create_tasks_and_semaphores(void)
{
	// Semaphores are useful to stop a Task proceeding, where it should be paused to wait,
	// because it is sharing a resource, such as the Serial port.
	// Semaphores should only be used whilst the scheduler is running, but we can set it up here.
	if ( xSemaphore == NULL )  // Check to confirm that the Semaphore has not already been created.
	{
		xSemaphore = xSemaphoreCreateMutex();  // Create a mutex semaphore.
		if ( ( xSemaphore ) != NULL )
		{
			xSemaphoreGive( ( xSemaphore ) );  // Make the mutex available for use, by initially "Giving" the Semaphore.
		}
	}

	xTaskCreate(
	task1
	,  "Task1"  // A name just for humans
	,  configMINIMAL_STACK_SIZE  // This stack size can be checked & adjusted by reading the Stack Highwater
	,  NULL
	,  2  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
	,  NULL );

	xTaskCreate(
	task2
	,  "Task2"  // A name just for humans
	,  configMINIMAL_STACK_SIZE  // This stack size can be checked & adjusted by reading the Stack Highwater
	,  NULL
	,  1  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
	,  NULL );
	
	xTaskCreate(
	temperatureHumiditySensorTask // the task body is in TemperatureHumidityManager.c
	,  "Grabbing temperature and humidity values from the sensors"  // A name just for humans
	,  configMINIMAL_STACK_SIZE  // This stack size can be checked & adjusted by reading the Stack Highwater
	,  NULL
	,  1  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
	,  NULL );
}

/*-----------------------------------------------------------*/
void task1( void *pvParameters )
{
	TickType_t xLastWakeTime;
	const TickType_t xFrequency = 5000/portTICK_PERIOD_MS; // 5000 ms

	// Initialise the xLastWakeTime variable with the current time.
	xLastWakeTime = xTaskGetTickCount();

	for(;;)
	{
		xTaskDelayUntil( &xLastWakeTime, xFrequency );
		puts("Task1 5 seconds gap."); // stdio functions are not reentrant - Should normally be protected by MUTEX
		PORTA ^= _BV(PA0);
	}
}

/*-----------------------------------------------------------*/
void task2( void *pvParameters )
{
	TickType_t xLastWakeTime;
	const TickType_t xFrequency = 10000/portTICK_PERIOD_MS; // 10000 ms

	// Initialise the xLastWakeTime variable with the current time.
	xLastWakeTime = xTaskGetTickCount();

	for(;;)
	{
		// CO2 measuring - here, just for testing purposes. Later on we'll find a better place for it.
		performCO2Measuring();
		
		xTaskDelayUntil( &xLastWakeTime, xFrequency );
		puts("Task2 10 seconds gap"); // stdio functions are not reentrant - Should normally be protected by MUTEX
		PORTA ^= _BV(PA7);
	}
}


/*-----------------------------------------------------------*/
void initialiseSystem()
{
	// Set output ports for leds used in the example
	DDRA |= _BV(DDA0) | _BV(DDA7);

	// Make it possible to use stdio on COM port 0 (USB) on Arduino board - Setting 57600,8,N,1
	stdio_initialise(ser_USART0);
	// Let's create some tasks
	create_tasks_and_semaphores();

	// vvvvvvvvvvvvvvvvv BELOW IS LoRaWAN initialisation vvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
	// Status Leds driver
	status_leds_initialise(5); // Priority 5 for internal task
	
	// The two lines below are copy-pasted from the official Guide.
	MessageBufferHandle_t downLinkMessageBufferHandle = xMessageBufferCreate(sizeof(lora_driver_payload_t)*2); // Here I make room for two downlink messages in the message buffer
	lora_driver_initialise(ser_USART1, downLinkMessageBufferHandle); // The parameter is the USART port the RN2483 module is connected to - in this case USART1 - here no message buffer for down-link messages are defined
	
	// Create LoRaWAN task and start it up with priority 3
	lora_handler_initialise(3, downLinkMessageBufferHandle);
	
	// initializing CO2 manager
	initializeCO2Manager();
	
	// Initialization and powering up a 7-segment display on the board. Here the call back function is not needed
	display_7seg_initialise(NULL);
	display_7seg_powerUp();
	
	// initializing temperature humidity driver
	if ( HIH8120_OK == hih8120_initialise() )
	{
       // Driver initialised OK
       // Always check what hih8120_initialise() returns
	}
}

/*-----------------------------------------------------------*/
int main(void)
{
	initialiseSystem(); // Must be done as the very first thing!!
	printf("Program Started!!\n");
	// showing a Pi number on the 7-segment display on the board (as an example).
	display_7seg_display(3.14159265359, 2);
	vTaskStartScheduler(); // Initialize and run the freeRTOS scheduler. Execution should never return from here.
	/* Replace with your application code */
	while (1)
	{
	}
}



/* a test comment from Rodrigo */
/* a second test comment from Rodrigo */