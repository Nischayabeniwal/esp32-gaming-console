#pragma once

#include "display_oled.h"
#include "input.h"

// ================= MENU STATES =================
enum MenuState {
  MENU_MAIN,
  MENU_CONNECT,
  MENU_INSTRUCTIONS,
  MENU_SHOW_IP,
  MENU_GAMES,
  MENU_GAME1,
  MENU_GAME2,
  MENU_GAME3
};

// ================= INTERNAL STATE =================
static MenuState currentMenu = MENU_MAIN;
static int cursor = 0;

// ================= HELPERS =================
void resetCursor() {
  cursor = 0;
}

// ================= DRAW FUNCTIONS =================
void drawMainMenu() {
  clearScreen();
  drawHeader("Main Menu");

  drawText(14, 16, "Connect Display");
  drawText(14, 26, "Games");

  drawArrow(cursor == 0 ? 16 : 26);
  display.display();
}

void drawConnectMenu() {
  clearScreen();
  drawHeader("Connect");

  drawText(14, 16, "Back");
  drawText(14, 26, "Instructions");
  drawText(14, 36, "Show IP");

  drawArrow(16 + cursor * 10);
  display.display();
}

void drawInstructionsMenu() {
  clearScreen();
  drawHeader("Instructions");

  drawText(14, 16, "Back");
  drawText(14, 26, "Text");

  drawArrow(16 + cursor * 10);
  display.display();
}

void drawShowIPMenu() {
  clearScreen();
  drawHeader("Show IP");

  drawText(14, 16, "Back");
  drawText(14, 26, "Use browser to play");

  drawArrow(16);
  display.display();
}

void drawGamesMenu() {
  clearScreen();
  drawHeader("Games");

  drawText(14, 16, "Back");
  drawText(14, 26, "Game 1");
  drawText(14, 36, "Game 2");
  drawText(14, 46, "Game 3");

  drawArrow(16 + cursor * 10);
  display.display();
}

void drawGameMenu(const char* title) {
  clearScreen();
  drawHeader(title);

  drawText(14, 16, "Exit Game");
  drawText(14, 26, "Reset");

  drawArrow(16 + cursor * 10);
  display.display();
}

// ================= MENU LOGIC =================
void handleMenu() {

  // ---------- INPUT ----------
  if (upPressed()) {
    cursor--;
  }

  if (downPressed()) {
    cursor++;
  }

  if (selectPressed()) {

    switch (currentMenu) {

      case MENU_MAIN:
        currentMenu = (cursor == 0) ? MENU_CONNECT : MENU_GAMES;
        resetCursor();
        break;

      case MENU_CONNECT:
        if (cursor == 0) currentMenu = MENU_MAIN;
        if (cursor == 1) currentMenu = MENU_INSTRUCTIONS;
        if (cursor == 2) currentMenu = MENU_SHOW_IP;
        resetCursor();
        break;

      case MENU_INSTRUCTIONS:
        currentMenu = MENU_CONNECT;
        resetCursor();
        break;

      case MENU_SHOW_IP:
        currentMenu = MENU_CONNECT;
        resetCursor();
        break;

      case MENU_GAMES:
        if (cursor == 0) currentMenu = MENU_MAIN;
        if (cursor == 1) currentMenu = MENU_GAME1;
        if (cursor == 2) currentMenu = MENU_GAME2;
        if (cursor == 3) currentMenu = MENU_GAME3;
        resetCursor();
        break;

      case MENU_GAME1:
      case MENU_GAME2:
      case MENU_GAME3:
        currentMenu = MENU_GAMES;
        resetCursor();
        break;
    }
  }

  // ---------- CURSOR LIMITS ----------
  int maxItems = 1;

  if (currentMenu == MENU_MAIN)        maxItems = 2;
  if (currentMenu == MENU_CONNECT)     maxItems = 3;
  if (currentMenu == MENU_INSTRUCTIONS)maxItems = 2;
  if (currentMenu == MENU_SHOW_IP)     maxItems = 1;
  if (currentMenu == MENU_GAMES)       maxItems = 4;
  if (currentMenu >= MENU_GAME1)       maxItems = 2;

  if (cursor < 0) cursor = maxItems - 1;
  if (cursor >= maxItems) cursor = 0;

  // ---------- DRAW ----------
  switch (currentMenu) {
    case MENU_MAIN:        drawMainMenu(); break;
    case MENU_CONNECT:     drawConnectMenu(); break;
    case MENU_INSTRUCTIONS:drawInstructionsMenu(); break;
    case MENU_SHOW_IP:     drawShowIPMenu(); break;
    case MENU_GAMES:       drawGamesMenu(); break;
    case MENU_GAME1:       drawGameMenu("Game 1"); break;
    case MENU_GAME2:       drawGameMenu("Game 2"); break;
    case MENU_GAME3:       drawGameMenu("Game 3"); break;
  }
}
