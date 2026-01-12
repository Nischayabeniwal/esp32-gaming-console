#pragma once

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "config.h"

// ================= FORWARD DECLARATIONS =================
void drawFrame();
void clearScreen();
void drawHeader(const char* title);
void drawArrow(int y);
void drawText(int x, int y, const char* text);
int  menuY(int index);

// ================= OLED INSTANCE =================
Adafruit_SSD1306 display(OLED_WIDTH, OLED_HEIGHT, &Wire, -1);

// ================= INTERNAL UI CONSTANTS =================
#define UI_MARGIN        2
#define UI_HEADER_Y      2
#define UI_HEADER_LINE_Y 12
#define UI_CONTENT_Y     16

// ================= INIT =================
void initDisplay() {
  Wire.begin(OLED_SDA, OLED_SCL);

  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    while (true) { delay(100); }
  }

  display.setRotation(2);        // LOCKED
  display.setTextColor(SSD1306_WHITE);
  display.clearDisplay();

  // Boot screen
  drawFrame();
  display.setTextSize(2);
  display.setCursor(18, 24);
  display.println("BOOT OK");
  display.display();
}

// ================= BASIC DRAWING =================
void clearScreen() {
  display.clearDisplay();
  drawFrame();   // always redraw boundary
}

// One-pixel border
void drawFrame() {
  display.drawRect(0, 0, OLED_WIDTH, OLED_HEIGHT, SSD1306_WHITE);
}

// ================= UI HELPERS =================
void drawHeader(const char* title) {
  display.setTextSize(1);
  display.setCursor(UI_MARGIN + 10, UI_HEADER_Y);
  display.println(title);

  display.drawLine(
    UI_MARGIN,
    UI_HEADER_LINE_Y,
    OLED_WIDTH - UI_MARGIN,
    UI_HEADER_LINE_Y,
    SSD1306_WHITE
  );
}

void drawArrow(int y) {
  display.setTextSize(1);
  display.setCursor(UI_MARGIN + 2, y);
  display.print(">");
}

void drawText(int x, int y, const char* text) {
  display.setTextSize(1);
  display.setCursor(x, y);
  display.println(text);
}

int menuY(int index) {
  return UI_CONTENT_Y + (index * 10);
}
