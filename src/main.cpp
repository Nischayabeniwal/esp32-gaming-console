#include "display_oled.h"
#include "input.h"
#include "user_setup.h"

void setup() {
  initInput();
  initDisplay();
  resetUserSetup();
}

void loop() {
  handleUserSetup();
}
