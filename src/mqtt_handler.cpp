// #include <WiFi.h>
// #include <PubSubClient.h>
// #include "config.h"
// #include "led_control.h"
// #include "mqtt_handler.h"

// WiFiClient espClient;
// PubSubClient mqttClient(espClient);
// IPAddress mqttBrokerIP;   // from gateway

// void mqttCallback(char* topic, byte* payload, unsigned int length) {
//   String message;
//   for (unsigned int i = 0; i < length; i++) {
//     message += (char)payload[i];
//   }
//   message.trim();
//   Serial.printf("MQTT received [%s]: %s\n", topic, message.c_str());

//   if (String(topic) == MQTT_TOPIC_CMD) {
//     if (message == "ON") {
//       turnOnLED();
//       publishStatusMQTT("ON");
//     } else if (message == "OFF") {
//       turnOffLED();
//       publishStatusMQTT("OFF");
//     }
//   }
// }

// void setupMQTT() {
//   // get gateway from wifi
//   mqttBrokerIP = WiFi.gatewayIP();
//   Serial.print("MQTT Broker IP (auto from gateway): ");
//   Serial.println(mqttBrokerIP.toString());

//   mqttClient.setServer(mqttBrokerIP, MQTT_PORT);
//   mqttClient.setCallback(mqttCallback);
//   Serial.println("MQTT client configured.");
// }

// void reconnectMQTT() {
//   if (mqttClient.connected()) return;

//   static unsigned long lastAttempt = 0;
//   unsigned long now = millis();
//   if (now - lastAttempt < 5000) return;
//   lastAttempt = now;

//   Serial.print("Connecting MQTT...");
//   String clientId = "ESP32-Lamp-" + String(WiFi.macAddress());
//   if (mqttClient.connect(clientId.c_str())) {
//     Serial.println("connected");
//     mqttClient.subscribe(MQTT_TOPIC_CMD);
//     publishStatusMQTT(isLEDOn() ? "ON" : "OFF");
//   } else {
//     Serial.print("failed, rc=");
//     Serial.print(mqttClient.state());
//     Serial.println(" (will retry later)");
//   }
// }

// void mqttLoop() {
//   reconnectMQTT();
//   mqttClient.loop();
// }

// void publishStatusMQTT(const char* state) {
//   if (mqttClient.connected()) {
//     mqttClient.publish(MQTT_TOPIC_STATUS, state, true);
//     Serial.printf("MQTT publish status: %s\n", state);
//   }
// }