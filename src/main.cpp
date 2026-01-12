#include <Arduino.h>
#include "config.h"
#include "display_oled.h"
#include "input.h"
#include "menu.h"

void setup() {
  initInput();
  initDisplay();
}

void loop() {
  handleMenu();
}
