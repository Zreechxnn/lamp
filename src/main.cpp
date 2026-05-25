#include <Arduino.h>
#include "config.h"
#include "wifi_mdns.h"
#include "led_control.h"
#include "web_server.h"

void setup() {
  Serial.begin(115200);
  setupLED();
  setupWiFi();
  setupMDNS();
  setupWebServer();
}

void loop() {
  server.handleClient();
}