#include <Arduino.h>
#include <libpax_api.h>
#include "Adafruit_NeoPixel.h"

struct count_payload_t count_from_libpax;


void process_count(void) {
  printf("pax: %lu; %lu; %lu;\n", count_from_libpax.pax, count_from_libpax.wifi_count, count_from_libpax.ble_count);
}

void init_Libpax() {
  struct libpax_config_t configuration; 
  libpax_default_config(&configuration);
  configuration.blecounter = 1;
  configuration.blescantime = 0; // infinit
  configuration.wifi_my_country = 1; // 1 = CH
  configuration.wificounter = 0; 
  configuration.wifi_channel_map = WIFI_CHANNEL_ALL;
  configuration.wifi_channel_switch_interval = 50;
  configuration.wifi_rssi_threshold = -80;
  configuration.ble_rssi_threshold = -80;
  libpax_update_config(&configuration);

  // internal processing initialization
  libpax_counter_init(process_count, &count_from_libpax, 10, 1); 
  libpax_counter_start();
}

#define PIN 21           // Pin connected to NeoPixel

Adafruit_NeoPixel strip = Adafruit_NeoPixel(1, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  
  strip.begin();
  strip.setBrightness(10);
  strip.setPixelColor(0, 255,0,0);
  strip.show();

  Serial.begin();

  init_Libpax();
  delay(500);


}


void loop() {
strip.setPixelColor(0, 0,255,0);
strip.show();

Serial.println(count_from_libpax.pax);
Serial.println(count_from_libpax.ble_count);
Serial.println(count_from_libpax.wifi_count);
}