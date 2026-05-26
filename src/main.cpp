#include <Arduino.h>
#include "config.h"
#include "wifi_mdns.h"
#include "led_control.h"
#include "web_server.h"
#include "mqtt_handler.h"
#include "ws_handler.h"

void setup() {
  Serial.begin(115200);
  setupLED();
  setupWiFi();
  setupMDNS();
  setupWebServer();
  setupMQTT();
  setupWebSocket();
  
}

void loop() {
  server.handleClient();
  mqttLoop();
  webSocket.loop();
}