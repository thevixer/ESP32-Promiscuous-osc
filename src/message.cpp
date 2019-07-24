#include "message.h"

Message::Message(){
    Serial.println("Default");
}

void Message::print(uint8_t id) const{
    switch (id)
    {
    case 2:
        Serial.printf("Msg: ID= %d, NAME= %s, VALUE_1 = %d, VALUE_2 = %d, VALUE_3 = %d \n", id, name, value_1, value_2, value_3);
        Serial.println(" ");
        break;
    case 1:
        Serial.printf("Msg: ID= %d, NAME= %s, VALUE_1 = %d, VALUE_2 = %d \n", id, name, value_1, value_2);
        Serial.println(" ");
        break;
    case 0:
        Serial.printf("Msg: ID= %d, NAME= %s, VALUE_1 = %d \n", id, name, value_1);
        Serial.println(" ");
        break;
    default:
        Serial.println("No valid Msg and arguments!");
        break;
    } 
}