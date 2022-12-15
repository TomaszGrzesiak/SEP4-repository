/*
 * downlinkHandler.c
 *
 * Created: 12-12-2022 22:10:27
 *  Author: Tomasz Grzesiak
 */ 

#include <lora_driver.h>
#include <stdio.h>
#include <semphr.h>

#include "definitions.h"

static lora_driver_payload_t downlinkPayload1;

void receiveNewMessageFromLoRaWaN( void *pvParameters );

void downlinkHandlerInitialise(UBaseType_t lora_handler_task_priority)
{	
	xTaskCreate(
	receiveNewMessageFromLoRaWaN // the task body is in downlinkHandler.c
	,  "Handling new messages from LoRaWaN"  // A name just for humans
	,  configMINIMAL_STACK_SIZE  // This stack size can be checked & adjusted by reading the Stack Highwater
	,  NULL
	,  lora_handler_task_priority  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
	,  NULL );
}

void receiveNewMessageFromLoRaWaN( void *pvParameters )
{
	for(;;)
	{
		// copied from the IoT Drivers documentation
		// this code must be in the loop of a FreeRTOS task!
		xMessageBufferReceive(downLinkMessageBufferHandle, &downlinkPayload1, sizeof(lora_driver_payload_t), portMAX_DELAY);
			printf("DOWN LINK: from port: %d with %d bytes received!\n", downlinkPayload1.portNo, downlinkPayload1.len);
		if (16 == downlinkPayload1.len) // Check that we have got the expected message
		{
			// decode the payload into our variables
			data.minCO2Setting = (downlinkPayload1.bytes[0] << 8) + downlinkPayload1.bytes[1];
			data.maxCO2Setting = (downlinkPayload1.bytes[2] << 8) + downlinkPayload1.bytes[3];
			data.minHumiditySetting = (downlinkPayload1.bytes[4] << 8) + downlinkPayload1.bytes[5];
			data.maxHumiditySetting = (downlinkPayload1.bytes[6] << 8) + downlinkPayload1.bytes[7];
			data.minTemperatureSetting = (downlinkPayload1.bytes[8] << 8) + downlinkPayload1.bytes[9];
			data.maxTemperatureSetting = (downlinkPayload1.bytes[10] << 8) + downlinkPayload1.bytes[11];
			data.minLightSetting = (downlinkPayload1.bytes[12] << 8) + downlinkPayload1.bytes[13];
			data.maxLightSetting = (downlinkPayload1.bytes[14] << 8) + downlinkPayload1.bytes[15];
			// printing the received values
			printf("Received settings: %d, %d, %d, %d, %d, %d, %d, %d\n",data.minCO2Setting,data.maxCO2Setting,data.minHumiditySetting,data.maxHumiditySetting,data.minTemperatureSetting,data.maxTemperatureSetting,data.minLightSetting,data.maxLightSetting);		
			
			// apperently, if a printf function has too long argument, it crashes all the program entirely, blocking even higher priority tasks, like lora_handler_task();
			// printf("Contrary to popular belief, Lorem Ipsum is not simply random text. It has roots in a piece of classical Latin literature from 45 BC, making it over 2000 years old. Richard McClintock, a Latin professor at Hampden-Sydney College in Virginia, looked up one of the more obscure Latin words, consectetur, from a Lorem Ipsum passage, and going through the cites of the word in classical literature, discovered the undoubtable source. Lorem Ipsum comes from sections. \n");
		}
	}
}