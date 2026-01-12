#pragma once

// ================= BUTTON PINS =================
// All buttons use INPUT_PULLUP (pressed = LOW)
#define BTN_UP       33
#define BTN_DOWN     26
#define BTN_LEFT     27
#define BTN_RIGHT    25
#define BTN_SELECT   32

// ================= OLED CONFIG =================
#define OLED_SDA     21
#define OLED_SCL     22
#define OLED_ADDR    0x3C
#define OLED_WIDTH   128
#define OLED_HEIGHT  64

// ================= TIMING =================
#define INPUT_DEBOUNCE_MS 200

// ================= WIFI =================
#define WIFI_SSID     "test" // Replace with your SSID 
#define WIFI_PASSWORD "21222726253332" // Replace with your Password
