#include <ESP8266WiFi.h>
extern "C" {
  #include "user_interface.h"
}

// List of real OUI (MAC address prefixes) from big companies
const uint8_t vendorOUIs[][3] = {
  {0x3C, 0x5A, 0xB4}, // Google
  {0xF4, 0xF5, 0xD8}, // Apple
  {0xDC, 0x53, 0x60}, // Samsung
  {0xFC, 0xFC, 0x48}, // Huawei
  {0xB4, 0xF0, 0xAB}, // Xiaomi
  {0x00, 0x1A, 0x11}, // Cisco
  {0xEC, 0x9B, 0xF3}, // OnePlus
  {0x70, 0x4F, 0x57}  // Sony
};

uint8_t beaconPacket[128];

void setup() {
  wifi_set_opmode(STATION_MODE);
  wifi_promiscuous_enable(0);
  wifi_set_channel(random(1, 12));
  Serial.begin(74880); // Optional debug
  randomSeed(micros());
}

void loop() {
  createRandomBeacon();
  wifi_send_pkt_freedom(beaconPacket, 128, 0);
  delay(10); // not too fast, avoid crash
}

// Generate random SSID and MAC
void createRandomBeacon() {
  memset(beaconPacket, 0, sizeof(beaconPacket));

  // Basic beacon frame header
  const uint8_t header[] = {
    0x80, 0x00,             // Frame Control
    0x00, 0x00,             // Duration
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, // Destination (broadcast)
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Source (to be set)
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // BSSID (same as source)
    0x00, 0x00              // Seq
  };
  memcpy(beaconPacket, header, sizeof(header));

  // Generate random MAC with real OUI
  uint8_t mac[6];
  int idx = random(sizeof(vendorOUIs) / 3);
  memcpy(mac, vendorOUIs[idx], 3);
  mac[3] = random(256);
  mac[4] = random(256);
  mac[5] = random(256);
  memcpy(beaconPacket + 10, mac, 6);
  memcpy(beaconPacket + 16, mac, 6);

  // Timestamp + beacon interval + capability info
  uint8_t fixedParams[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Timestamp
    0x64, 0x00, // Interval (0.1s)
    0x01, 0x04  // Capabilities
  };
  memcpy(beaconPacket + 24, fixedParams, sizeof(fixedParams));

  // SSID element
  beaconPacket[36] = 0x00; // Tag: SSID
  uint8_t ssidLen = random(6, 16);
  beaconPacket[37] = ssidLen;
  for (int i = 0; i < ssidLen; i++) {
    beaconPacket[38 + i] = 32 + random(95); // ASCII printable
  }

  // Supported Rates element (dummy)
  uint8_t ratePos = 38 + ssidLen;
  beaconPacket[ratePos++] = 0x01; // Tag: Supported Rates
  beaconPacket[ratePos++] = 0x08;
  memcpy(&beaconPacket[ratePos], "\x82\x84\x8b\x96\x24\x30\x48\x6c", 8);

  // Optional: Change channel every few seconds (done outside)
}
