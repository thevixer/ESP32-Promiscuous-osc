#include "wifi_connection.h"
#include <WiFi.h>



#define maxCh 13

const char *ssid = "OnePlus6";
const char *pwd = "vikiscool";
const IPAddress ip(192, 168, 43, 120);
IPAddress gateway;
const IPAddress subnet(255, 255, 255, 0);

uint8_t curChannel = 1;
int8_t rssi_limit = -97;
uint8_t listcount = 0;
String maclist[64][3];
String mac_host;


const wifi_promiscuous_filter_t filt = {
    .filter_mask = WIFI_PROMIS_FILTER_MASK_MGMT | WIFI_PROMIS_FILTER_MASK_DATA};

void add_mac(String addr, int8_t rssi) {

  bool added = false;

  for (int i = 0; i <= 63; i++) {
    if (addr == maclist[i][0]) {
      if (maclist[i][1] == "OFFLINE") {
        maclist[i][1] = "0";
      }
      added = true;
    }
  }

  if (!added) {
    maclist[listcount][0] = addr;
    maclist[listcount][1] = "0";
    maclist[listcount][2] = abs(rssi);
    listcount++;

    if (listcount >= 64) {
      Serial.println("Mac array full resetting!");
      listcount = 0;
    }
  }
}

IRAM_ATTR void sniffer(void *buf, wifi_promiscuous_pkt_type_t type) {
  const wifi_promiscuous_pkt_t *pkt = (wifi_promiscuous_pkt_t *)buf;
  const wifi_packet_t *snifed_packed = (wifi_packet_t *)pkt->payload;
  const mac_hdr_t *mac_header = &snifed_packed->hdr;
  const uint16_t pkt_length = pkt->rx_ctrl.sig_len - sizeof(mac_hdr_t);

  if (pkt->rx_ctrl.rssi > rssi_limit || pkt_length > 0) {
    String mac_to_str;
    for (uint8_t i = 0; i < 6; i++) {
      mac_to_str += String(mac_header->sa[i], HEX);
    }
    add_mac(mac_to_str, pkt->rx_ctrl.rssi);
  }
}

void setup_wifi_promiscous() {
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
  Serial.println("--------------------------");
  Serial.println("Start sniffing for packets!");
  Serial.println("--------------------------");
}
String IpAddress2String(IPAddress& ipAddress){
  return String(ipAddress[0]) + String(".") + \
         String(ipAddress[1]) + String(".") + \
         String(ipAddress[2]) + String(".") + \
         String(ipAddress[3])  ;
}
void setup_wifi_osc_mode() {
  if (!WiFi.isConnected()) {
    WiFi.begin(ssid, pwd);
  }

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("--------------------------");
  Serial.println("Connected to hotspot!");
  Serial.println("--------------------------");
  gateway = WiFi.gatewayIP();
  mac_host = IpAddress2String(gateway);
  WiFi.config(ip, gateway, subnet);
}

String get_host(){
  String host = IpAddress2String(gateway);
  return host;
}

void update_mac_addresses() {
  for (int i = 0; i <= 63; i++) {
    if (!(maclist[i][0] == "")) {
      if (!(maclist[i][2].toInt() < rssi_limit)) {
        maclist[i][1] = String(maclist[i][1].toInt() + 1);
      } else {
        maclist[i][1] = "OFFLINE";
      }
    }
  }
}

void check_channel() {
  if (curChannel > maxCh) {
    curChannel = 1;
  }

  esp_wifi_set_channel(curChannel, WIFI_SECOND_CHAN_NONE);
  delay(1000);
}

void change_to_promisc() {
    WiFi.disconnect(true);
    Serial.println("--------------------------");
    Serial.println("Disconnected wifi mode.");
    Serial.println("--------------------------");
    delay(1000);
    setup_wifi_promiscous();
}

void change_to_wifi_osc(){
    ESP_ERROR_CHECK(esp_wifi_set_promiscuous(false));
    Serial.println("--------------------------");
    Serial.println("Disconnected promiscuous mode.");
    Serial.println("--------------------------");
    delay(1000);
    setup_wifi_osc_mode();
}