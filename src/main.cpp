/*
MIT License
https://github.com/hideakitai/ArduinoOSC
Copyright (c) 2017 Hideaki Tai
*/
#include "main.h"
#include <WiFiUdp.h>
#include <OSCMessage.h>
#include <ArduinoOSC.h>

//---------------------------- CONTROL & COUNT
uint32_t time_sinds_start;
uint32_t time_in_current_mode = 0;
const uint32_t time_to_complete = 20000;

//---------------------------- SENSORS 
const String gsr_sensor = "GSR";
const String heartRateSensor = "MAX30105";
const String wifiInfo = "WiFi";

//---------------------------- OSC
//WiFiUDP Udp;
OscWiFi osc;
IPAddress host;
const char addr[15] = "/mac/addresses";
const uint16_t recv_port = 10000;
const uint16_t send_port = 12000;
String test = "Testystringy";


void setup() {
  Serial.begin(115200);
  setup_wifi_promiscous();
  initMax();
}

void loop() {
  time_sinds_start = millis();
  

  if (time_sinds_start >= time_in_current_mode + time_to_complete) {
    change_to_wifi_osc();
    //Udp.begin(recv_port);
    host = get_host();


    

    //uint16_t size_array = sizeof(maclist)/sizeof(maclist[0][0]);
    //Serial.println(size_array);
    // osc.parse seems to be throwing the error I can't really figure out why...

    //sensor_to_container(0, gsr_sensor, getGsrData());
    //sensor_to_container(1, heartRateSensor, getIrSensorValue(), getAvgBpm());

    for(uint16_t i = 0; i < 64; i++){
      if(maclist[i][0].length() > 11){
        osc.begin(recv_port);
        osc.parse();
        osc.send(host.toString(), send_port, addr, maclist[i][0], maclist[i][2]);
        Serial.print("Send OSC MAC = ");Serial.print(maclist[i][0]);Serial.print(" RSSI = ");Serial.println(maclist[i][2]);
        delay(100);
      }
    }
    delay(1000);
    change_to_promisc();
    time_in_current_mode = time_sinds_start;
  }

    update_mac_addresses();
    getHeartRateData();

    Serial.print("Sniff ");
  
} 