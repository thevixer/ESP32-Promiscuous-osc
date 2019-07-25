
#include "gsr.h"
#include "sensor.h"

const int GSR = A2;
uint16_t gsr_average;
uint16_t sensorValue;

const uint8_t amount_of_sensors = 1;
Sensor sensor_container[amount_of_sensors];

uint16_t getGsrData()
{
    uint32_t sum = 0;
    for (uint8_t i = 0; i < 10; i++)
    {
        sensorValue = analogRead(GSR);
        sum += sensorValue;
    }
    gsr_average = map(sum * 0.1, 0, 4096, 0, 512);
    return gsr_average;
}

void sensor_to_container(uint8_t id, String name, uint16_t value_1, uint16_t value_2, uint16_t value_3)
{
    if (value_1 != 0 && value_3 != 0 && value_2 != 0)
    {
        Sensor sensor = {id, name, value_1, value_2, value_3};
        sensor_container[id] = sensor;
        Serial.printf("%i -> ", id);
        sensor_container[id].print(2);
    }
    if (value_1 != 0 && value_2 != 0)
    {
        Sensor sensor = {id, name, value_1, value_2};
        sensor_container[id] = sensor;
        Serial.printf("%i -> ", id);
        sensor_container[id].print(1);
    }
    if (value_1 != 0)
    {
        Sensor sensor = {id, name, value_1};
        sensor_container[id] = sensor;
        Serial.printf("%i -> ", id);
        sensor_container[id].print(0);
    }
    else
    {
        Serial.print("No valid sensor data.");
    }
}