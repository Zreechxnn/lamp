#include "ws_handler.h"
#include "config.h"

WebSocketsServer webSocket(81); 

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
  
}

void setupWebSocket() {
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
  Serial.println("WebSocket server started on port 81");
}

void broadcastStatus(const char* state) {
  String json = "{\"status\":\"" + String(state) + "\"}";
  webSocket.broadcastTXT(json);
  Serial.println("WS broadcast: " + json);
}