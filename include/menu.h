#pragma once

#include "display_oled.h"
#include "input.h"
#include "wifi_logic.h"

// ===== boot_menu hook (implemented in boot_menu.h) =====
void goToBootMenu();

// ================= MENU STATES =================
enum MenuState {
  MENU_MAIN,
  MENU_SETTINGS,
  MENU_INSTRUCTIONS,
  MENU_CONSOLE_INFO,
  MENU_CONNECT_SCREEN,
  MENU_SHOW_IP,
  MENU_GAMES,
  MENU_GAME
};

// ================= INTERNAL STATE =================
static MenuState menuState = MENU_MAIN;
static int cursor = 0;
static int currentGame = 0; // 0=Snake,1=Pong,2=Tetris

// ================= UTIL =================
void resetCursor() {
  cursor = 0;
}

// ================= DRAW FUNCTIONS =================
void drawMainMenu() {
  clearScreen();
  drawHeader("Main Menu");

  drawText(18, menuY(0), "Settings");
  drawText(18, menuY(1), "Games");
  drawText(18, menuY(2), "Back");

  drawArrow(menuY(cursor));
  display.display();
}

void drawSettingsMenu() {
  clearScreen();
  drawHeader("Settings");

  drawText(18, menuY(0), "Instructions");
  drawText(18, menuY(1), "Show IP");
  drawText(18, menuY(2), "Back");

  drawArrow(menuY(cursor));
  display.display();
}

void drawInstructionsMenu() {
  clearScreen();
  drawHeader("Instructions");

  drawText(18, menuY(0), "Console Overview");
  drawText(18, menuY(1), "Connect Game Screen");
  drawText(18, menuY(2), "Back");

  drawArrow(menuY(cursor));
  display.display();
}

void drawConsoleInfo() {
  clearScreen();
  drawHeader("Console Info");

  drawText(6, menuY(0), "ESP32 = Console");
  drawText(6, menuY(1), "OLED = Menu UI");
  drawText(6, menuY(2), "Buttons = Control");
  drawText(6, menuY(3), "Browser = Screen");

  drawText(18, menuY(5), "Back");
  drawArrow(menuY(cursor));
  display.display();
}

void drawConnectScreenInfo() {
  clearScreen();
  drawHeader("Game Screen");

  drawText(6, menuY(0), "1. Settings > Show IP");
  drawText(6, menuY(1), "2. Note IP address");
  drawText(6, menuY(2), "3. Open browser");
  drawText(6, menuY(3), "4. http://<ip>");
  drawText(6, menuY(4), "5. Start gaming");

  drawText(18, menuY(6), "Back");
  drawArrow(menuY(cursor));
  display.display();
}

void drawShowIPMenu() {
  clearScreen();
  drawHeader("Network");

  if (isWiFiConnected()) {
    drawText(18, menuY(0), "IP Address:");
    drawText(18, menuY(1), getIPAddress().c_str());
  } else {
    drawText(18, menuY(0), "WiFi not connected");
  }

  drawText(18, menuY(3), "Back");
  drawArrow(menuY(cursor));
  display.display();
}

void drawGamesMenu() {
  clearScreen();
  drawHeader("Games");

  drawText(18, menuY(0), "Snake");
  drawText(18, menuY(1), "Pong");
  drawText(18, menuY(2), "Tetris");
  drawText(18, menuY(3), "Back");

  drawArrow(menuY(cursor));
  display.display();
}

void drawGamePlaceholder() {
  clearScreen();
  drawHeader("Game");

  drawText(18, menuY(0), "Game running...");
  drawText(18, menuY(1), "Back");

  drawArrow(menuY(cursor));
  display.display();
}

// ================= MENU ENGINE =================
void handleMenu() {

  // -------- INPUT --------
  if (upPressed())   cursor--;
  if (downPressed()) cursor++;

  if (selectPressed()) {

    switch (menuState) {

      case MENU_MAIN:
        if (cursor == 0) menuState = MENU_SETTINGS;
        else if (cursor == 1) menuState = MENU_GAMES;
        else if (cursor == 2) { goToBootMenu(); return; }
        resetCursor();
        break;

      case MENU_SETTINGS:
        if (cursor == 0) menuState = MENU_INSTRUCTIONS;
        else if (cursor == 1) menuState = MENU_SHOW_IP;
        else if (cursor == 2) menuState = MENU_MAIN;
        resetCursor();
        break;

      case MENU_INSTRUCTIONS:
        if (cursor == 0) menuState = MENU_CONSOLE_INFO;
        else if (cursor == 1) menuState = MENU_CONNECT_SCREEN;
        else if (cursor == 2) menuState = MENU_SETTINGS;
        resetCursor();
        break;

      case MENU_CONSOLE_INFO:
        if (cursor == 5) menuState = MENU_INSTRUCTIONS;
        resetCursor();
        break;

      case MENU_CONNECT_SCREEN:
        if (cursor == 6) menuState = MENU_INSTRUCTIONS;
        resetCursor();
        break;

      case MENU_SHOW_IP:
        if (cursor == 3) menuState = MENU_SETTINGS;
        resetCursor();
        break;

      case MENU_GAMES:
        if (cursor <= 2) {
          currentGame = cursor;
          menuState = MENU_GAME;
        } else {
          menuState = MENU_MAIN;
        }
        resetCursor();
        break;

      case MENU_GAME:
        if (cursor == 1) menuState = MENU_GAMES;
        resetCursor();
        break;
    }
  }

  // -------- CURSOR LIMITS --------
  int maxItems = 1;

  switch (menuState) {
    case MENU_MAIN:           maxItems = 3; break;
    case MENU_SETTINGS:       maxItems = 3; break;
    case MENU_INSTRUCTIONS:   maxItems = 3; break;
    case MENU_CONSOLE_INFO:   maxItems = 6; break;
    case MENU_CONNECT_SCREEN: maxItems = 7; break;
    case MENU_SHOW_IP:        maxItems = 4; break;
    case MENU_GAMES:          maxItems = 4; break;
    case MENU_GAME:           maxItems = 2; break;
  }

  if (cursor < 0) cursor = maxItems - 1;
  if (cursor >= maxItems) cursor = 0;

  // -------- DRAW --------
  switch (menuState) {
    case MENU_MAIN:           drawMainMenu(); break;
    case MENU_SETTINGS:       drawSettingsMenu(); break;
    case MENU_INSTRUCTIONS:   drawInstructionsMenu(); break;
    case MENU_CONSOLE_INFO:   drawConsoleInfo(); break;
    case MENU_CONNECT_SCREEN: drawConnectScreenInfo(); break;
    case MENU_SHOW_IP:        drawShowIPMenu(); break;
    case MENU_GAMES:          drawGamesMenu(); break;
    case MENU_GAME:           drawGamePlaceholder(); break;
  }
}
