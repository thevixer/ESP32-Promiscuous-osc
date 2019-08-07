#ifndef _WIFI_SNIFF_H
#define _WIFI_SNIFF_H
#include <Arduino.h>
#include <WiFi.h>
#include "esp_wifi.h"

typedef struct // Struct voor de MAC Header
{
  unsigned frame_ctrl: 16;
  unsigned duration: 16;
  uint8_t da[6];    //receiver address
  uint8_t sa[6];    // sender address
  uint8_t bssid[6]; // filtering address
  unsigned sequence_ctrl: 16;
  uint8_t addr4[6]; // Optional?
} mac_hdr_t;

typedef struct // Struct voor de WiFi packeten
{ 
  mac_hdr_t hdr;
  uint8_t payload[0];
} wifi_packet_t;

void check_channel();

void add_mac(String addr, int8_t rssi);
void update_mac_addresses();

void setup_wifi_promiscous();
IRAM_ATTR void sniffer(void *buf, wifi_promiscuous_pkt_type_t type);

#endif