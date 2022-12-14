/*
 * CO2Servo.c
 *
 * Created: 14-12-2022 01:45:30
 *  Author: Tomasz
 */ 

#include <rc_servo.h>

void inititialize_CO2_servo(void);
void CO2_servo_task(void);

void inititialize_CO2_Servo(void) {
	rc_servo_initialise();
	rc_servo_setPosition(0, -100);
}

void CO2_servo_task(void){
	
}

