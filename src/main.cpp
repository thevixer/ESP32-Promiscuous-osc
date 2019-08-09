/*
MIT License 
https://github.com/hideakitai/ArduinoOSC
Copyright (c) 2017 Hideaki Tai 
*/
#include "main.h"

//String maclist[64];
//uint8_t listcount; 

//---------------------------- OSC --------------------------------------
OscWiFi osc;
String host;
// const uint16_t recv_port = 10000;
// const uint16_t send_port = 12000;

//---------------------------- CONTROL & COUNT --------------------------------------
int times_run = 0;
uint32_t time_sinds_start;
uint32_t time_in_current_mode = 0;
const uint32_t time_to_complete = 20000; // time in ms
bool wifi_state;

//---------------------------- SENSORS --------------------------------------
const String gsr_sensor = "GSR";
const String heartRateSensor = "MAX30105";
const String wifiInfo = "WiFi";

void serial_print_stuff()
{
  Serial.printf("There have %.2fs passed since start, executed %i times\n", time_sinds_start * 0.001, times_run);
  Serial.println("------------------------------------------------------------");
}

void setup()
{
  Serial.begin(115200);
  setup_wifi_promiscous();
  initMax();

  // osc.begin(recv_port);
  // String osc_send_succes = "Succes";
  // bool send = true;
  // osc.send(host, send_port, "/start", osc_send_succes, send);

} //--- setup()

void loop()
{
  time_sinds_start = millis();

  if(time_sinds_start >= time_in_current_mode + time_to_complete)
  {
    wifi_state = !wifi_state;
    change_wifi_mode(wifi_state);
    time_in_current_mode = time_sinds_start;
  }
  //


  if(!wifi_state)
  {
    update_mac_addresses();
    getHeartRateData();
  }
  if(wifi_state)
  {
    osc.parse();
    sensor_to_container(0, gsr_sensor, getGsrData());
    sensor_to_container(1, heartRateSensor, getIrSensorValue(), getAvgBpm());
    for(uint8_t i = 0; i < listcount; i++)
    {
      Serial.print("MAC: ");Serial.print(maclist[i][0]);Serial.print(" ");
      Serial.print("RSSI: ");Serial.println(maclist[i][2]);
    }
  }

  times_run++;
  Serial.printf("TIMES RAN: %d, TSS: %d, TICM: %d \n", times_run, time_sinds_start, time_in_current_mode);
} //--- loop()