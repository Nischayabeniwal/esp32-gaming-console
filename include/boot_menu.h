#pragma once

#include "display_oled.h"
#include "input.h"
#include "menu.h"

// ================= BOOT STATES =================
enum BootState {
  BOOT_ANIMATION,
  BOOT_START_MENU,
  BOOT_DONE
};

static BootState bootState = BOOT_ANIMATION;

// ================= ANIMATION STATE =================
static int animX = 10;
static int animY = 20;
static int velX  = 2;
static int velY  = 1;

// ================= BOOT MENU STATE =================
static int bootCursor = 0;

// ================= HELPERS =================
bool anyButtonPressed() {
  return upPressed() || downPressed() ||
         leftPressed() || rightPressed() ||
         selectPressed();
}

// ================= BOOT ANIMATION =================
void drawBootAnimation() {
  clearScreen();

  animX += velX;
  animY += velY;

  if (animX <= 2 || animX >= OLED_WIDTH - 20) velX *= -1;
  if (animY <= 14 || animY >= OLED_HEIGHT - 10) velY *= -1;

  drawText(animX, animY, "<>");
  display.display();
}

// ================= BOOT MENU =================
void drawBootMenu() {
  clearScreen();

  // BlackBoxx stylized title
  display.setTextSize(2);
  display.setCursor(14, 12);
  display.println("BlackBox");

  display.setCursor(56, 28); // second x moved to next line
  display.println("x");

  display.setTextSize(1);
  drawText(28, 46, "Create User");
  drawText(28, 56, "Enter Menu");

  drawArrow(bootCursor == 0 ? 46 : 56);
  display.display();
}
void resetBootState() {
  bootState = BOOT_START_MENU;
}

// ================= BOOT HANDLER =================
void handleBootMenu() {

  switch (bootState) {

    case BOOT_ANIMATION:
      drawBootAnimation();
      if (anyButtonPressed()) {
        bootState = BOOT_START_MENU;
        delay(250);
      }
      break;

    case BOOT_START_MENU:
      if (upPressed() || downPressed()) {
        bootCursor = !bootCursor;
      }

      if (selectPressed()) {
        if (bootCursor == 1) {
          bootState = BOOT_DONE; // Enter Menu
        }
        // Create User intentionally empty
      }

      drawBootMenu();
      break;

    case BOOT_DONE:
      handleMenu();   // hand over control
      break;
  }
}
