#pragma once

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "config.h"

// ================= OLED INSTANCE =================
// Global display object
Adafruit_SSD1306 display(OLED_WIDTH, OLED_HEIGHT, &Wire, -1);

// ================= INIT =================
void initDisplay() {
  Wire.begin(OLED_SDA, OLED_SCL);

  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    // Hard stop if OLED init fails
    while (true) { delay(100); }
  }

  display.setRotation(2);                 // LOCKED orientation
  display.setTextColor(SSD1306_WHITE);
  display.clearDisplay();

  // Boot test screen
  display.setTextSize(2);
  display.setCursor(10, 20);
  display.println("BOOT OK");
  display.display();
}

// ================= BASIC DRAW HELPERS =================
void clearScreen() {
  display.clearDisplay();
}

void drawHeader(const char* title) {
  display.setTextSize(1);
  display.setCursor(14, 0);
  display.println(title);
}

void drawArrow(int y) {
  display.setTextSize(1);
  display.setCursor(0, y);
  display.print(">");
}

void drawText(int x, int y, const char* text) {
  display.setTextSize(1);
  display.setCursor(x, y);
  display.println(text);
}
