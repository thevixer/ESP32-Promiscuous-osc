#include "main.h"

//---------------------------- WIFI --------------------------------------
const char* ssid = "OnePlus6";
const char* pwd = "vikiscool";
const IPAddress ip(192,168,43,120);
IPAddress gateway;
const IPAddress subnet(255,255,255,0);

//---------------------------- OSC --------------------------------------
OscWiFi osc;
String host;
const uint16_t recv_port = 10000;
const uint16_t send_port = 12000;

//---------------------------- MSG --------------------------------------
const int amount_of_sensor = 1;
Message sensorMsg[amount_of_sensor];
int times_run = 0;

//---------------------------- SENSORS --------------------------------------

const String gsr_sensor = "GSR";

//---------------------------- COUNTER --------------------------------------

const int period = 1000;
unsigned long time_now = 0;

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, pwd);
  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");delay(500);
  }

  gateway = WiFi.gatewayIP(); // Onze gateway IP = onze host IP. Dit omdat de smartphone in AP mode staat en zijn eigen IP = gatewayIP.
  host = String(gateway);
  WiFi.config(ip, gateway, subnet);

  Serial.print("WiFi connected,      IP = "); Serial.println(WiFi.localIP());
  Serial.print("WiFi connected, GATEWAY = "); Serial.println(gateway);

  osc.begin(recv_port);
  String osc_send_succes = "Succes";
  bool send = true;
  osc.send(host, send_port, "/start", osc_send_succes, send);



}//--- setup()

void sensorToMsg(String name, uint16_t value_1, uint16_t value_2 = 0, uint16_t value_3 = 0){
  for(uint8_t i = 0; i < amount_of_sensor; i++){
    if(value_1 != 0 && value_3 != 0 && value_2 != 0)
    {
          Message sensor = {i, name, value_1, value_2, value_3};
          sensorMsg[i] = sensor;
          Serial.print("3 args -> ");sensorMsg[i].print();
    }
    if (value_1 != 0 && value_2 != 0)
    {
          Message sensor = {i, name, value_1, value_2};
          sensorMsg[i] = sensor;
          Serial.print("2 args -> ");sensorMsg[i].print();
    }
    if (value_1 != 0)
    {
        Message sensor = {i, name, value_1};
        sensorMsg[i] = sensor;
        Serial.printf("%i -> ", i);sensorMsg[i].print();
    }
    else
    {
      Serial.print("No valid sensor data.");
    }
    
    

  }
}

void loop() {
  time_now = millis();
  osc.parse();

  if(time_now % period == 0){
    times_run++;
    Serial.printf("There have %2.fs passed since start, executed %i times\n", time_now*0.001, times_run);
    Serial.println("------------------------------------------------------------");
    Serial.print("Msg[] size: "); Serial.printf("%i", sizeof(sensorMsg)); Serial.print(" | ");
    sensorToMsg(gsr_sensor, getGsrData());
  }

  //git test
  

}//--- loop()