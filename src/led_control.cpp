#include <Arduino.h>
#include "config.h"
#include "led_control.h"

static bool ledState = false;

void setupLED() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
}

void turnOnLED() {
  digitalWrite(LED_PIN, HIGH);
  ledState = true;
  Serial.println("LED ON");
}

void turnOffLED() {
  digitalWrite(LED_PIN, LOW);
  ledState = false;
  Serial.println("LED OFF");
}

bool isLEDOn() {
  return ledState;
}