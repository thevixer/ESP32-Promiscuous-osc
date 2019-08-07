/*
MIT License 
https://github.com/hideakitai/ArduinoOSC
Copyright (c) 2017 Hideaki Tai 
*/
#include "main.h"

//---------------------------- WIFI --------------------------------------
const char *ssid = "OnePlus6";
const char *pwd = "vikiscool";
const IPAddress ip(192, 168, 43, 120);
IPAddress gateway;
const IPAddress subnet(255, 255, 255, 0);

//---------------------------- OSC --------------------------------------
OscWiFi osc;
String host;
const uint16_t recv_port = 10000;
const uint16_t send_port = 12000;

//---------------------------- CONTROL & COUNT --------------------------------------
int times_run = 0;
const int period = 1000;
unsigned long start_time = 0;
unsigned long time_after_function = 0;
uint8_t amount_of_readings = 0;

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
  initMax();
  delay(500);
  WiFi.begin(ssid, pwd);
  delay(500);

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");delay(500);
  }
  gateway = WiFi.gatewayIP(); // Onze gateway IP = onze host IP. Dit omdat de smartphone in AP mode staat en zijn eigen IP = gatewayIP.
  host = String(gateway);
  WiFi.config(ip, gateway, subnet);

  //---------- MAX30105 INIT --------------
  

  osc.begin(recv_port);
  String osc_send_succes = "Succes";
  bool send = true;
  osc.send(host, send_port, "/start", osc_send_succes, send);

} //--- setup()

void loop()
{
  start_time = millis();
  osc.parse();
  
  getHeartRateData();
  times_run++;
  //serial_print_stuff();
  sensor_to_container(0, gsr_sensor, getGsrData());
  sensor_to_container(1, heartRateSensor, getIrSensorValue(), getAvgBpm());
  //sensor_to_container(2, wifiInfo, 10, 200, 5000);
} //--- loop()