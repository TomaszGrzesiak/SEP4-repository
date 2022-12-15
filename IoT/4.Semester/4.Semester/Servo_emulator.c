/*
 * Servo_emulator.c
 *
 * Created: 14-12-2022 01:56:52
 *  Author: Tomasz
 */ 

#include <rc_servo.h>
#include <stdio.h>
#include "Servo_emulator.h"
#include <string.h>
#include <stdlib.h>

typedef struct servoEmulator{
	char servoName[32];
	int servoNumber;
	int position;
} servoEmulator;

// the constructor below is based on code snippets delivered by IHA during the semester course
servoEmulator_t servoEmulator_create(char* servoName, uint16_t servoNumber, uint16_t position) { // Constructor
	servoEmulator_t _newServoEmulator = calloc(sizeof(servoEmulator), 1);

	if (NULL == _newServoEmulator) { // There was not enough memory
		return NULL;
	}

	_newServoEmulator->servoNumber = servoNumber;
	_newServoEmulator->position = position;
	strncpy(_newServoEmulator->servoName, servoName, sizeof(_newServoEmulator->servoName) - 1);

	return _newServoEmulator;
}

void servoEmulatorSetPosition(servoEmulator_t self, uint16_t position) {
	printf("%s power: %d%%\n",self->servoName, position);
}