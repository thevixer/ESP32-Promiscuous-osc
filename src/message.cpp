#include "message.h"

Message::Message(){
    Serial.println("Default");
}
/* Message::Message(uint8_t id, char name, uint16_t value_1){
    Serial.println("Message with 3 arg and 1 values");
}
Message::Message(uint8_t id, char name, uint16_t value_1, uint16_t value_2){
    Serial.println("Message with 4 arg and 2 values");
}

Message::Message(uint8_t id, char name, uint16_t value_1, uint16_t value_2, uint16_t value_3){
    Serial.println("Message with 4 arg and 2 values");
} */

void Message::print() const{
    // if(value_3 =)
    // {
    //     Serial.printf("Msg: ID= %d, NAME= %s, VALUE_1 = %d, VALUE_2 = %d, VALUE_3 = %d \n", id, name, value_1, value_2, value_3);
    // }
    // else if( != 0)
    // {
    //     Serial.printf("Msg: ID= %d, NAME= %s, VALUE_1 = %d, VALUE_2 = %d \n", id, name, value_1, value_2);
    // }
        Serial.printf("Msg: ID= %d, NAME= %s, VALUE_1 = %d \n", id, name, value_1);
        Serial.println(" ");
  
}