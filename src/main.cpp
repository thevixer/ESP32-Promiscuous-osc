/*
MIT License 
https://github.com/hideakitai/ArduinoOSC
Copyright (c) 2017 Hideaki Tai 
*/
#include "main.h"

//---------------------------- OSC --------------------------------------
// OscWiFi osc;
// String host;
// const uint16_t recv_port = 10000;
// const uint16_t send_port = 12000;

//---------------------------- CONTROL & COUNT --------------------------------------
int times_run = 0;
const int period = 1000;
unsigned long start_time = 0;
unsigned long time_after_function = 0;
uint8_t amount_of_readings = 0;

bool wifi_state;

//---------------------------- SENSORS --------------------------------------
const String gsr_sensor = "GSR";
const String heartRateSensor = "MAX30105";
const String wifiInfo = "WiFi";

void serial_print_stuff()
{
  Serial.printf("There have %.2fs passed since start, executed %i times\n", start_time * 0.001, times_run);
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
  start_time = millis();
  //osc.parse();

  if(!wifi_state)
  {
    update_mac_addresses();
    getHeartRateData();
  }
  else if(wifi_state)
  {
  sensor_to_container(0, gsr_sensor, getGsrData());
  sensor_to_container(1, heartRateSensor, getIrSensorValue(), getAvgBpm());
  }
  else
  {
    Serial.println("Something went wrong man...");
  }
  
  times_run++;
} //--- loop()