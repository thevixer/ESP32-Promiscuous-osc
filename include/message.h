#ifndef _MESSAGE_
#define _MESSAGE_
#include <Arduino.h>

const String unk = "unknown";

class Message
{
        const char _name = unk.c_str;
        const uint16_t _value = 0;


    public:
        Message();
        Message(const char & name, const uint16_t & value);
        ~Message();
        void print() const;
        

};


#endif