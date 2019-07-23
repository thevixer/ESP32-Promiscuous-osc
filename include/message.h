#ifndef _MESSAGE_
#define _MESSAGE_
#include <Arduino.h>

const String unk = "unknown";

class Message
{
    public:
        uint8_t id;
        String name;
        uint16_t value_1;
        uint16_t value_2;
        uint16_t value_3;
     

        Message();

        Message(uint8_t id, String name, uint16_t value_1){
            this->id = id;
            this->value_1 = value_1;
            this->name = name;
        };

        Message(uint8_t id, String name, uint16_t value_1, uint16_t value_2){
            this->id = id;
            this->value_1 = value_1;
            this->value_2 = value_2;
            this->name = name;
        };

        Message(uint8_t id, String name, uint16_t value_1, uint16_t value_2, uint16_t value_3){
            this->id = id;
            this->value_1 = value_1;
            this->value_2 = value_2;
            this->value_3 = value_3;
            this->name = name;
        };

        ~Message(){};

        void print() const;
        

};


#endif