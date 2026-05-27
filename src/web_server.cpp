#include <WebServer.h>
#include <LittleFS.h>
#include "config.h"
#include "led_control.h"
#include "web_server.h"
// #include "mqtt_handler.h"

WebServer server(80);

void handleOn() {
  turnOnLED();
  // publishStatusMQTT("ON");
  server.send(200, "text/plain", "ON");
}

void handleOff() {
  turnOffLED();
  // publishStatusMQTT("OFF");
  server.send(200, "text/plain", "OFF");
}

void handleStatus() {
  server.send(200, "text/plain", isLEDOn() ? "ON" : "OFF");
}

void setupWebServer() {
  if (!LittleFS.begin(true)) {
    Serial.println("❌ LittleFS mount failed!");
  } else {
    Serial.println("✅ LittleFS mounted.");
  }

  server.on("/on", HTTP_GET, handleOn);
  server.on("/off", HTTP_GET, handleOff);
  server.on("/status", HTTP_GET, handleStatus);

  server.on("/", HTTP_GET, []() {
    File file = LittleFS.open("/index.html", "r");
    if (file) {
      server.streamFile(file, "text/html");
      file.close();
    } else {
      server.send(404, "text/plain", "index.html not found");
    }
  });

  server.serveStatic("/", LittleFS, "/");

  server.onNotFound([]() {
    server.send(404, "text/plain", "Halaman tidak ditemukan");
  });

  server.begin();
  Serial.println("Web server dimulai di port 80");
}