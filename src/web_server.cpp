#include <WebServer.h>
#include <LittleFS.h>
#include "config.h"
#include "led_control.h"
#include "web_server.h"

WebServer server(80);

void handleOn() {
  turnOnLED();
  server.send(200, "text/plain", "ON");
}

void handleOff() {
  turnOffLED();
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
    if (LittleFS.exists("/index.html")) {
      File file = LittleFS.open("/index.html", "r");
      server.streamFile(file, "text/html");
      file.close();
    } else {
      server.send(200, "text/html", "<h1>❌ File HTML Hilang!</h1><p>Pastikan Upload Filesystem Image berhasil.</p>");
    }
  });

  server.serveStatic("/", LittleFS, "/");

  server.onNotFound([]() {
    server.send(404, "text/plain", "Halaman tidak ditemukan");
  });

  server.begin();
  Serial.println("Web server dimulai di port 80");
}