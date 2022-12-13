/*
 * CO2Manager.h
 *
 * Created: 30-11-2022 00:02:36
 *  Author: Tomasz Grzesiak
 */ 
#include <stdint.h>

void myCo2CallBack(uint16_t ppm);
void initializeCO2Manager();
void performCO2Measuring();
uint16_t getCO2ppm();