#include <Arduino.h>
#include "config.h"
#include "led_control.h"
#include "ws_handler.h"

static bool ledState = false;

void setupLED() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
}

void turnOnLED() {
  digitalWrite(LED_PIN, HIGH);
  ledState = true;
  Serial.println("LED ON");
  broadcastStatus("ON");
}

void turnOffLED() {
  digitalWrite(LED_PIN, LOW);
  ledState = false;
  Serial.println("LED OFF");
  broadcastStatus("OFF");
}

bool isLEDOn() {
  return ledState;
}