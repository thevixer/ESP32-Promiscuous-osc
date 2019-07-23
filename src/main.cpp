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
const int amount_of_sensor = 2;
Message sensorMsg[amount_of_sensor];

//---------------------------- SENSORS --------------------------------------

uint16_t GSR;

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

void sensorToMsg(char name, uint16_t value){
  for(uint8_t i = 0; i <= amount_of_sensor; i++){
    Message sensor = {i, name, value};
    sensorMsg[i] = sensor;
  }
}

void loop() {

  osc.parse();
  GSR = getGsrData();
  //git test
  

}//--- loop()