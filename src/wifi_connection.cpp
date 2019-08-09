#include "wifi_connection.h"

#define maxCh 13         //max Channel -> US = 11, EU = 13, Japan = 14

const char *ssid = "OnePlus6";
const char *pwd = "vikiscool";
const IPAddress ip(192, 168, 43, 120);
IPAddress gateway;
const IPAddress subnet(255, 255, 255, 0);


uint8_t curChannel = 1;
int8_t rssi_limit = -97;
uint8_t listcount = 0;
String maclist[64][3];
uint8_t attempt = 0;

const wifi_promiscuous_filter_t filt = // filter the packets with type of WIFI_PKT_MGMT | filter the packets with type of WIFI_PKT_DATA
    {
        .filter_mask = WIFI_PROMIS_FILTER_MASK_MGMT | WIFI_PROMIS_FILTER_MASK_DATA 
};

void add_mac(String addr, int8_t rssi)
{
 
  bool added = false;


  for (int i = 0; i <= 63; i++)  
  { 
    if (addr == maclist[i][0]) // checks if the MAC address has been added before
    {
      if(maclist[i][1] == "OFFLINE") // Check if it was offline and has come back to reset timer
      {
        maclist[i][1] = "0";
      }
      //Serial.println("OLD mac: " + addr + " with an rssi of -" + maclist[listcount][2]);
      //Serial.println(" ");
      added = true;
    }
  }

  if (!added) // if not added voeg een nieuw MAC addres toe.
  {
    maclist[listcount][0] = addr;
    maclist[listcount][1] = "0";
    maclist[listcount][2] = abs(rssi);
    //Serial.println("NEW mac: " + addr + " with an rssi of -" + maclist[listcount][2]);
    //Serial.println(" ");
    listcount++;

    if (listcount >= 64) // MAC array heeft x aantal plaatsen check als deze vol zit daarna resetten. 
    {
      Serial.println("Mac array full resetting!");
      listcount = 0;
    }
  }
}

IRAM_ATTR void sniffer(void *buf, wifi_promiscuous_pkt_type_t type) //Dit is de callback function waar de WiFi packeten naar toe gestuurd worden.
{
  const wifi_promiscuous_pkt_t *pkt = (wifi_promiscuous_pkt_t *)buf;
  const wifi_packet_t *snifed_packed = (wifi_packet_t *)pkt->payload;
  const mac_hdr_t *mac_header = &snifed_packed->hdr;

  const uint16_t pkt_length = pkt->rx_ctrl.sig_len - sizeof(mac_hdr_t);


  if (pkt->rx_ctrl.rssi < rssi_limit || pkt_length < 0) // Controleer of signaal(RSSI) goed genoeg is > 0. RSSI is niet altijd volledig betrouwbaar
  {                                   // aangezien verschillende fabrikanten andere waardes gebruiken. 0-60, 0-255, ...
    //Serial.printf("WiFi RSSI %d lower than limit %d, ignoring packet.\n", pkt->rx_ctrl.rssi, rssi_limit);
  }
  else
  {
    
/*     Serial.printf("CHAN=%02d, RSSI=%02d, SA=%02x:%02x:%02x:%02x:%02x:%02x\n", pkt->rx_ctrl.channel, pkt->rx_ctrl.rssi, 
    mac_header->sa[0],mac_header->sa[1],mac_header->sa[2], mac_header->sa[3],mac_header->sa[4],mac_header->sa[5]); */

    String mac_to_str;
    for (uint8_t i = 0; i < 6; i++)
    {
      mac_to_str += String(mac_header->sa[i], HEX);
    }
    //Serial.println(mac_to_str);
    add_mac(mac_to_str, pkt->rx_ctrl.rssi); // Signaal goed genoeg toevoegen maar!
  }
} //Sniffer

void setup_wifi_promiscous()
{
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    cfg.wifi_task_core_id = 0;
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    ESP_ERROR_CHECK(esp_wifi_set_storage(WIFI_STORAGE_RAM));
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_NULL));
    ESP_ERROR_CHECK(esp_wifi_stop());
    ESP_ERROR_CHECK(esp_wifi_set_promiscuous_filter(&filt));
    ESP_ERROR_CHECK(esp_wifi_set_promiscuous_rx_cb(&sniffer));
    ESP_ERROR_CHECK(esp_wifi_set_promiscuous(true));
    ESP_ERROR_CHECK(esp_wifi_set_channel(curChannel, WIFI_SECOND_CHAN_NONE));
    Serial.println("starting promiscous mode!");
    wifi_state = false;
    delay(1000);// delay is niet goed maar wel nodig hier

}

void setup_wifi_osc_mode(){
  WiFi.begin(ssid, pwd);
  delay(5000);
  if(WiFi.status() == WL_CONNECTED)
  {
    attempt = 0;
    Serial.println("Connected to hotspot!");
    gateway = WiFi.gatewayIP(); // Onze gateway IP = onze host IP. Dit omdat de smartphone in AP mode staat en zijn eigen IP = gatewayIP.
    host = String(gateway);
    wifi_state = true;
    WiFi.config(ip, gateway, subnet);
  }
  if(WiFi.status() == WL_CONNECT_FAILED)
  {
    attempt++;
    Serial.println("Connection failed...");
    delay(1000);
    Serial.print("Retrying to reconnect, attempt: ");Serial.println(attempt);
    setup_wifi_osc_mode();
  }
  if(WiFi.status() == WL_CONNECTION_LOST)
  {
    attempt++;
    Serial.println("Connection lost...");
    delay(1000);
    Serial.print("Trying to reconnect, attempt: ");Serial.println(attempt);
    setup_wifi_osc_mode();
  }

}

void update_mac_addresses(){
  for (int i = 0; i <= 63; i++)
  {
    if (!(maclist[i][0] == "")) // check if mac is set
    {
      if (!(maclist[i][2].toInt() < rssi_limit)) // check if rssi  -80
      {
        maclist[i][1] = String(maclist[i][1].toInt() + 1);
        String active = (maclist[i][1] == "OFFLINE") ? "." : "s";
      }
      else
      {
        maclist[i][1] = "OFFLINE";
      }
    }
  }
}

void check_channel(){
  if (curChannel > maxCh)
  {
    curChannel = 1;
  }

   esp_wifi_set_channel(curChannel, WIFI_SECOND_CHAN_NONE);
   delay(1000);
}

void change_wifi_mode(bool wifi_state){
  if(wifi_state)
  {
    //release promiscuous mode
    WiFi.mode(WIFI_OFF);
    Serial.println("Disconnected promiscuous mode.");
    delay(500);
    setup_wifi_osc_mode();
  }
  else
  {
    //release connection to app
    WiFi.mode(WIFI_OFF);
    Serial.println("Disconnected wifi mode.");
    delay(500);
    setup_wifi_promiscous();
  }
}