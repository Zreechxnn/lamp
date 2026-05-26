#ifndef WS_HANDLER_H
#define WS_HANDLER_H

#include <WebSocketsServer.h>

extern WebSocketsServer webSocket;

void setupWebSocket();
void broadcastStatus(const char* state);

#endif