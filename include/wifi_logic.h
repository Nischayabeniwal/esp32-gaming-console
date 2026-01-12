#pragma once

#include <WiFi.h>
#include "config.h"

// ================= INTERNAL STATE =================
static bool _wifiConnected = false;

// ================= INIT =================
void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  unsigned long startAttempt = millis();

  // Try for max 10 seconds
  while (WiFi.status() != WL_CONNECTED &&
         millis() - startAttempt < 10000) {
    delay(300);
  }

  _wifiConnected = (WiFi.status() == WL_CONNECTED);
}

// ================= STATUS =================
bool isWiFiConnected() {
  return _wifiConnected;
}

// ================= INFO =================
String getIPAddress() {
  if (!_wifiConnected) return String("Not Connected");
  return WiFi.localIP().toString();
}

String getSSID() {
  if (!_wifiConnected) return String("None");
  return WiFi.SSID();
}
