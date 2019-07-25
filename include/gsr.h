#ifndef _GSR_H
#define _GSR_H
#include <Arduino.h>

uint16_t getGsrData();
void sensor_to_container(uint8_t id, String name, uint16_t value_1, uint16_t value_2 = 0, uint16_t value_3 = 0);

#endif