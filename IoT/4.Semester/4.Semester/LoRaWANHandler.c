/*
* loraWANHandler.c
*
* Created: 12/04/2019 10:09:05
*  Author: IHA
*/
#include <stddef.h>
#include <stdio.h>

#include <ATMEGA_FreeRTOS.h>

#include <lora_driver.h>
#include <status_leds.h>

#include "definitions.h"

// Parameters for OTAA join - You have got these in a mail from IHA
#define LORA_appEUI "05ABE2835032EC3E"
#define LORA_appKEY "B90973872CFD40F5E380185AD43FC18C"

void lora_handler_task( void *pvParameters );

static lora_driver_payload_t _uplink_payload;

// following 3 lines are copy-pasted from The Quick Start Guide in the Ib Havn's GitHub
lora_driver_payload_t downlinkPayload;
uint16_t minCO2Setting; // Max Humidity
uint16_t maxCO2Setting; // Max Temperature
MessageBufferHandle_t downLinkMessageBufferHandle;


// moved here from a for loop in lora_handler_task, so that the 3 fields are more global
static uint16_t co2_ppm = 0; // unsigned int is always positive 0 to 4294967295
static uint16_t hum = 0;
static uint16_t light = 0;
static int16_t temp = 0; // int16_t (signed int) may be negative -2147483648 to 2147483647

void lora_handler_initialise(UBaseType_t lora_handler_task_priority, MessageBufferHandle_t adhd)
{
	downLinkMessageBufferHandle = adhd;
	xTaskCreate(
	lora_handler_task
	,  "LRHand"  // A name just for humans
	,  configMINIMAL_STACK_SIZE+200  // This stack size can be checked & adjusted by reading the Stack Highwater
	,  NULL
	,  lora_handler_task_priority  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
	,  NULL );
}

static void _lora_setup(void)
{
	char _out_buf[20];
	lora_driver_returnCode_t rc;
	status_leds_slowBlink(led_ST2); // OPTIONAL: Led the green led blink slowly while we are setting up LoRa

	// Factory reset the transceiver
	printf("FactoryReset >%s<\n", lora_driver_mapReturnCodeToText(lora_driver_rn2483FactoryReset()));
	
	// Configure to EU868 LoRaWAN standards
	printf("Configure to EU868 >%s<\n", lora_driver_mapReturnCodeToText(lora_driver_configureToEu868()));

	// Get the transceivers HW EUI
	rc = lora_driver_getRn2483Hweui(_out_buf);
	printf("Get HWEUI >%s<: %s\n",lora_driver_mapReturnCodeToText(rc), _out_buf);

	// Set the HWEUI as DevEUI in the LoRaWAN software stack in the transceiver
	printf("Set DevEUI: %s >%s<\n", _out_buf, lora_driver_mapReturnCodeToText(lora_driver_setDeviceIdentifier(_out_buf)));

	// Set Over The Air Activation parameters to be ready to join the LoRaWAN
	printf("Set OTAA Identity appEUI:%s appKEY:%s devEUI:%s >%s<\n", LORA_appEUI, LORA_appKEY, _out_buf, lora_driver_mapReturnCodeToText(lora_driver_setOtaaIdentity(LORA_appEUI,LORA_appKEY,_out_buf)));

	// Save all the MAC settings in the transceiver
	printf("Save mac >%s<\n",lora_driver_mapReturnCodeToText(lora_driver_saveMac()));

	// Enable Adaptive Data Rate
	printf("Set Adaptive Data Rate: ON >%s<\n", lora_driver_mapReturnCodeToText(lora_driver_setAdaptiveDataRate(LORA_ON)));

	// Set receiver window1 delay to 500 ms - this is needed if down-link messages will be used
	printf("Set Receiver Delay: %d ms >%s<\n", 500, lora_driver_mapReturnCodeToText(lora_driver_setReceiveDelay(500)));

	// Join the LoRaWAN
	uint8_t maxJoinTriesLeft = 100;
	
	do {
		rc = lora_driver_join(LORA_OTAA);
		printf("Join Network TriesLeft:%d >%s<\n", maxJoinTriesLeft, lora_driver_mapReturnCodeToText(rc));

		if ( rc != LORA_ACCEPTED)
		{
			// Make the red led pulse to tell something went wrong
			status_leds_longPuls(led_ST1); // OPTIONAL
			// Wait 5 sec and lets try again
			vTaskDelay(pdMS_TO_TICKS(5000UL));
		}
		else
		{
			break;
		}
	} while (--maxJoinTriesLeft);

	if (rc == LORA_ACCEPTED)
	{
		// Connected to LoRaWAN :-)
		// Make the green led steady
		status_leds_ledOn(led_ST2); // OPTIONAL
	}
	else
	{
		// Something went wrong
		// Turn off the green led
		status_leds_ledOff(led_ST2); // OPTIONAL
		// Make the red led blink fast to tell something went wrong
		status_leds_fastBlink(led_ST1); // OPTIONAL

		// Lets stay here
		while (1)
		{
			taskYIELD();
		}
	}
}

/*-----------------------------------------------------------*/
void lora_handler_task( void *pvParameters )
{
	// Hardware reset of LoRaWAN transceiver
	lora_driver_resetRn2483(1);
	vTaskDelay(2);
	lora_driver_resetRn2483(0);
	// Give it a chance to wakeup
	vTaskDelay(150);

	lora_driver_flushBuffers(); // get rid of first version string from module after reset!

	_lora_setup();

	_uplink_payload.len = 8;
	_uplink_payload.portNo = 2;

	TickType_t xLastWakeTime;
	
	const uint16_t timeInterval = 30; // Upload message every XX seconds 
	const TickType_t xFrequency = pdMS_TO_TICKS(timeInterval * 1000);
	xLastWakeTime = xTaskGetTickCount();
	
	for(;;)
	{

		printf(">> attempting to send and receive data each %d seconds...\n",timeInterval);
				
		// Some dummy payload
		hum = 51914; // Dummy humidity HEX: CACA
		temp = 48316; // Dummy temp HEX: BCBC
		co2_ppm = getCO2ppm(); // no longer so dummy CO2
		light = 43947; // Dummy light HEX: ABAB
		

		_uplink_payload.bytes[0] = data.humidity >> 8;
		_uplink_payload.bytes[1] = data.humidity & 0xFF;
		_uplink_payload.bytes[2] = data.temperature >> 8;
		_uplink_payload.bytes[3] = data.temperature & 0xFF;
		_uplink_payload.bytes[4] = co2_ppm >> 8;
		_uplink_payload.bytes[5] = co2_ppm & 0xFF;
		_uplink_payload.bytes[6] = light >> 8;
		_uplink_payload.bytes[7] = light & 0xFF;

		status_leds_shortPuls(led_ST4);  // OPTIONAL
		printf("Upload Message >%s<\n", lora_driver_mapReturnCodeToText(lora_driver_sendUploadMessage(false, &_uplink_payload)));
		
		xMessageBufferReceive(downLinkMessageBufferHandle, &downlinkPayload, sizeof(lora_driver_payload_t), pdMS_TO_TICKS(2500));
		printf("DOWN LINK: from port: %d with %d bytes received!\n", downlinkPayload.portNo, downlinkPayload.len); // Just for Debug
		
		
		if (4 == downlinkPayload.len) // Check that we have got the expected 4 bytes
		{
			// decode the payload into our variables
			minCO2Setting = (downlinkPayload.bytes[0] << 8) + downlinkPayload.bytes[1];
			maxCO2Setting = (downlinkPayload.bytes[2] << 8) + downlinkPayload.bytes[3];
			printf("DOWN LINK first 2 bytes: %d, and the other 2 bytes: %d\n", minCO2Setting, maxCO2Setting); // Just for Debug
		}
		
		xTaskDelayUntil( &xLastWakeTime, xFrequency );
	}
}
