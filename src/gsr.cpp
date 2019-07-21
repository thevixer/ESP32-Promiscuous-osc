
#include "gsr.h"

const int GSR = A2;
uint16_t gsr_average;
uint16_t sensorValue;

void getGsrData(){
    uint32_t sum = 0;
    for(uint8_t i = 0; i < 10; i++){
        sensorValue = analogRead(GSR);
        sum += sensorValue;
    }
    gsr_average = map(sum * 0.1, 0, 4096, 0, 512);
}
