#include <Arduino.h>
#include "config.h"
#include "display_oled.h"
#include "input.h"

int y = 16;

void setup() {
  initInput();
  initDisplay();
}

void loop() {
  clearScreen();
  drawHeader("BUTTON TEST");

  if (upPressed())    y -= 10;
  if (downPressed())  y += 10;

  if (leftPressed())  drawText(60, 48, "LEFT");
  if (rightPressed()) drawText(60, 48, "RIGHT");
  if (selectPressed()) drawText(50, 48, "SELECT");

  if (y < 16) y = 16;
  if (y > 56) y = 56;

  drawArrow(y);
  display.display();
}
