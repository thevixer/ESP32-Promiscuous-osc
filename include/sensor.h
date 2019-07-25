#ifndef _Sensor_
#define _Sensor_
#include <Arduino.h>

class Sensor
{
    uint8_t id;
    const char *name;
    uint16_t value_1;
    uint16_t value_2;
    uint16_t value_3;

public:
    Sensor();

    Sensor(uint8_t id, String name, uint16_t value_1)
    {
        this->id = id;
        this->name = name.c_str();
        this->value_1 = value_1;
    };

    Sensor(uint8_t id, String name, uint16_t value_1, uint16_t value_2)
    {
        this->id = id;
        this->name = name.c_str();
        this->value_1 = value_1;
        this->value_2 = value_2;
    };

    Sensor(uint8_t id, String name, uint16_t value_1, uint16_t value_2, uint16_t value_3)
    {
        this->id = id;
        this->name = name.c_str();
        this->value_1 = value_1;
        this->value_2 = value_2;
        this->value_3 = value_3;
    };

    ~Sensor(){};

    void print(uint8_t id) const;
};

#endif