#include "message.h"

Message::Message(){
    Serial.println("Default");
}

Message::Message(const char & name, const uint16_t & value) : _name(name), _value(value){
    Serial.println("Message with args");
}

void Message::print() const{
    Serial.printf("%c value = %d \n", _name, _value);
}