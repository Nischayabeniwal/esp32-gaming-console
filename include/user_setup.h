#pragma once

#include "display_oled.h"
#include "input.h"

// ================= STATES =================
enum UserState {
  USER_SELECT,
  USER_CONFIRM_SELECT,
  PASSWORD_CREATE,
  PASSWORD_CONFIRM,
  EDIT_USERS,
  RESET_CONFIRM,
  USER_DONE
};

static UserState state = USER_SELECT;

// ================= USERS =================
static const char* users[3] = { "Alpha", "Bravo", "Charlie" };

// ================= PASSWORD DATA =================
static const char symbols[4] = { '#', '$', '@', '&' };
static char passwords[3][5] = { "", "", "" }; // 3 users, max 4 chars + null

static int cursor = 0;
static int selectedUser = -1;

// temp password being created
static char tempPass[5];
static int tempLen = 0;

// ================= RESET =================
void resetUserSetup() {
  state = USER_SELECT;
  cursor = 0;
  selectedUser = -1;
  tempLen = 0;
  tempPass[0] = '\0';
}

// ================= INVERTED CONFIRM SCREEN =================
void drawConfirm(const char* title, bool yesSelected) {
  display.clearDisplay();
  display.fillRect(0, 0, OLED_WIDTH, OLED_HEIGHT, SSD1306_WHITE);

  display.setTextColor(SSD1306_BLACK);
  display.setTextSize(1);

  display.setCursor(34, 16);
  display.println(title);

  display.setCursor(30, 36);
  display.print(yesSelected ? "> Yes   No" : "  Yes > No");

  display.setTextColor(SSD1306_WHITE);
  display.display();
}

// ================= DRAW SCREENS =================
void drawUserSelect() {
  clearScreen();
  drawHeader("Select User");

  for (int i = 0; i < 3; i++) {
    drawText(18, menuY(i), users[i]);
  }
  drawText(18, menuY(3), "Edit Users");

  drawArrow(menuY(cursor));
  display.display();
}

void drawPasswordCreate() {
  clearScreen();
  drawHeader("Create Password");

  drawText(18, menuY(0), "Use Symbols");

  for (int i = 0; i < 4; i++) {
    char buf[4];
    snprintf(buf, sizeof(buf), "[%c]", symbols[i]);
    drawText(10 + i * 22, menuY(1), buf);
  }
  drawText(10 + 4 * 22, menuY(1), "[OK]");

  // horizontal cursor
  display.setCursor(14 + cursor * 22, menuY(2));
  display.print("^");

  drawText(18, menuY(4), "Pass:");
  drawText(60, menuY(4), tempPass);

  display.display();
}

void drawEditUsers() {
  clearScreen();
  drawHeader("Edit Users");

  for (int i = 0; i < 3; i++) {
    char buf[20];
    snprintf(buf, sizeof(buf), "%s [%c]",
             users[i],
             strlen(passwords[i]) > 0 ? 'X' : 'O');
    drawText(18, menuY(i), buf);
  }

  drawText(18, menuY(3), "Back");
  drawArrow(menuY(cursor));
  display.display();
}

// ================= MAIN HANDLER =================
void handleUserSetup() {

  if (upPressed()) cursor--;
  if (downPressed()) cursor++;

  if (leftPressed() && state == PASSWORD_CREATE && cursor > 0) cursor--;
  if (rightPressed() && state == PASSWORD_CREATE && cursor < 4) cursor++;

  if (selectPressed()) {

    switch (state) {

      // -------- USER SELECT --------
      case USER_SELECT:
        if (cursor < 3) {
          selectedUser = cursor;
          state = USER_CONFIRM_SELECT;
          cursor = 0;
        } else {
          state = EDIT_USERS;
          cursor = 0;
        }
        break;

      // -------- CONFIRM USER --------
      case USER_CONFIRM_SELECT:
        if (cursor == 0) {
          tempLen = 0;
          tempPass[0] = '\0';
          state = PASSWORD_CREATE;
          cursor = 0;
        } else {
          state = USER_SELECT;
          cursor = 0;
        }
        break;

      // -------- PASSWORD CREATE --------
      case PASSWORD_CREATE:
        if (cursor < 4 && tempLen < 4) {
          tempPass[tempLen++] = symbols[cursor];
          tempPass[tempLen] = '\0';
        } else if (cursor == 4 && tempLen == 4) {
          state = PASSWORD_CONFIRM;
          cursor = 0;
        }
        break;

      // -------- CONFIRM PASSWORD --------
      case PASSWORD_CONFIRM:
        if (cursor == 0) {
          strcpy(passwords[selectedUser], tempPass);
          state = USER_DONE;
        } else {
          tempLen = 0;
          tempPass[0] = '\0';
          state = PASSWORD_CREATE;
          cursor = 0;
        }
        break;

      // -------- EDIT USERS --------
      case EDIT_USERS:
        if (cursor < 3) {
          selectedUser = cursor;
          state = RESET_CONFIRM;
          cursor = 0;
        } else {
          state = USER_SELECT;
          cursor = 0;
        }
        break;

      // -------- RESET CONFIRM --------
      case RESET_CONFIRM:
        if (cursor == 0) {
          passwords[selectedUser][0] = '\0'; // reset
          state = EDIT_USERS;
        } else {
          state = EDIT_USERS;
        }
        cursor = 0;
        break;

      default:
        break;
    }
  }

  // -------- CURSOR LIMITS --------
  int maxItems = 1;
  if (state == USER_SELECT) maxItems = 4;
  if (state == USER_CONFIRM_SELECT) maxItems = 2;
  if (state == PASSWORD_CREATE) maxItems = 5;
  if (state == PASSWORD_CONFIRM) maxItems = 2;
  if (state == EDIT_USERS) maxItems = 4;
  if (state == RESET_CONFIRM) maxItems = 2;

  if (cursor < 0) cursor = maxItems - 1;
  if (cursor >= maxItems) cursor = 0;

  // -------- DRAW --------
  switch (state) {
    case USER_SELECT:
      drawUserSelect();
      break;

    case USER_CONFIRM_SELECT:
      drawConfirm("Select user?", cursor == 0);
      break;

    case PASSWORD_CREATE:
      drawPasswordCreate();
      break;

    case PASSWORD_CONFIRM:
      drawConfirm("Save password?", cursor == 0);
      break;

    case EDIT_USERS:
      drawEditUsers();
      break;

    case RESET_CONFIRM:
      drawConfirm("Reset password?", cursor == 0);
      break;

    case USER_DONE:
      // handled by caller
      break;
  }
}

// ================= STATUS =================
bool isUserSetupDone() {
  return state == USER_DONE;
}

const char* getActiveUser() {
  return (selectedUser >= 0) ? users[selectedUser] : "";
}
