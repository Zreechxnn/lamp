#include <WiFi.h>
#include <ESPmDNS.h>
#include "config.h"
#include "wifi_mdns.h"

struct WifiCredentials {
  const char* ssid;
  const char* password;
};

const WifiCredentials wifiList[] = {
  { WIFI_SSID_1, WIFI_PASS_1 },
  { WIFI_SSID_2, WIFI_PASS_2 }
};
const int wifiCount = sizeof(wifiList) / sizeof(wifiList[0]);

void setupWiFi() {
  WiFi.mode(WIFI_STA);
  for (int i = 0; i < wifiCount; i++) {
    Serial.printf("\nMencoba WiFi: %s", wifiList[i].ssid);
    WiFi.begin(wifiList[i].ssid, wifiList[i].password);
    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 20) {
      delay(500);
      Serial.print(".");
      attempts++;
    }
    if (WiFi.status() == WL_CONNECTED) {
      Serial.printf("\nTerhubung ke %s, IP: %s\n",
                    wifiList[i].ssid,
                    WiFi.localIP().toString().c_str());
      return;
    } else {
      Serial.printf("\nGagal terhubung ke %s", wifiList[i].ssid);
    }
  }
  Serial.println("\nSemua SSID gagal. ESP32 akan restart...");
  delay(3000);
  ESP.restart();
}

void setupMDNS() {
  if (!MDNS.begin(MDNS_HOSTNAME)) {
    Serial.println("❌ Gagal memulai mDNS!");
    return;
  }
  MDNS.addService("http", "tcp", 80);
  Serial.println("✅ mDNS berhasil dimulai");
  Serial.printf("   Hostname: %s.local\n", MDNS_HOSTNAME);
}