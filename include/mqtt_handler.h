#ifndef MQTT_HANDLER_H 
#define MQTT_HANDLER_H

#include <IPAddress.h>

extern IPAddress mqttBrokerIP;

void setupMQTT();
void mqttLoop();
void publishStatusMQTT(const char* status);

#endif