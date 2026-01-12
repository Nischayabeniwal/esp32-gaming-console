#pragma once

#include <Arduino.h>
#include "config.h"

// ================= INTERNAL STATE =================
static unsigned long _lastPressTime = 0;

// ================= INIT =================
void initInput() {
  pinMode(BTN_UP, INPUT_PULLUP);
  pinMode(BTN_DOWN, INPUT_PULLUP);
  pinMode(BTN_LEFT, INPUT_PULLUP);
  pinMode(BTN_RIGHT, INPUT_PULLUP);
  pinMode(BTN_SELECT, INPUT_PULLUP);
}

// ================= DEBOUNCE =================
bool _debounced() {
  unsigned long now = millis();
  if (now - _lastPressTime > INPUT_DEBOUNCE_MS) {
    _lastPressTime = now;
    return true;
  }
  return false;
}

// ================= BUTTON QUERIES =================
bool upPressed() {
  return (digitalRead(BTN_UP) == LOW) && _debounced();
}

bool downPressed() {
  return (digitalRead(BTN_DOWN) == LOW) && _debounced();
}

bool leftPressed() {
  return (digitalRead(BTN_LEFT) == LOW) && _debounced();
}

bool rightPressed() {
  return (digitalRead(BTN_RIGHT) == LOW) && _debounced();
}

bool selectPressed() {
  return (digitalRead(BTN_SELECT) == LOW) && _debounced();
}
