#include <Arduino.h>
#include "config.h"
#include "display_oled.h"
#include "input.h"
#include "wifi_logic.h"

void setup() {
  initDisplay();
  initInput();
  initWiFi();
}

void loop() {
  clearScreen();
  drawHeader("WiFi Test");

  if (isWiFiConnected()) {
    drawText(14, 16, "Connected");
    drawText(14, 26, getSSID().c_str());
    drawText(14, 36, getIPAddress().c_str());
  } else {
    drawText(14, 16, "Not Connected");
  }

  display.display();
}
