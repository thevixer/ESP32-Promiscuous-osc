#ifndef _GSD_H
#define _GSD_H
#include <Arduino.h>

uint16_t getGsrData();
uint16_t getIrSensorValue();
uint16_t getBpm();
int getAvgBpm();

void getHeartRateData();
void initMax();
void sensor_to_container(uint8_t id, String name, uint16_t value_1, int value_2 = 0, uint16_t value_3 = 0);

#endif