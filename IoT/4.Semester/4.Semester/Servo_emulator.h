/*
 * Servo_emulator.c
 *
 * Created: 14-12-2022 01:48:05
 *  Author: Tomasz
 */ 

#include <rc_servo.h>
#include <stdio.h>

typedef struct servoEmulator* servoEmulator_t;
servoEmulator_t servoEmulator_create(char* servoName, uint16_t uinservoNumber, uint16_t position);
void servoEmulatorSetPosition(servoEmulator_t self, uint16_t position);