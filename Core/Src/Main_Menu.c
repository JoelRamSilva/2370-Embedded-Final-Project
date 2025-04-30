/*
 * Main_Menu.c
 *
 *  Created on: Apr 16, 2025
 *      Author: joelrsilva
 */


#include "Main_Menu.h"

const char* menu_items[MENU_ITEM_COUNT] = { "EASY", "MEDIUM", "HARD" };
int current_selection = 0;
GameState current_state = STATE_MENU;

void DrawMenu() {
    LCD_Clear(0, LCD_COLOR_WHITE);
    LCD_DisplayString(70, 60, "SELECT");
    LCD_DisplayString(45, 80, "DIFFICULTY:");

    for (int i = 0; i < MENU_ITEM_COUNT; i++) {
        uint16_t y = 160 + i * 30;
        if (i == current_selection) {
            LCD_DisplayString(30, y, "->");
        }
        LCD_DisplayString(70, y, menu_items[i]);
    }
}

void HandleMenuInput(void) {
    static bool previous_state = false;
    static uint32_t press_time = 0;

    bool current_button = Button_IsPressed();
    uint32_t now = HAL_GetTick();

    if (current_button && !previous_state) {
        press_time = now;
    }

    if (!current_button && previous_state) {
        uint32_t duration = now - press_time;

        if (duration < 500) {
            // Short press to cycle selection
            current_selection = (current_selection + 1) % MENU_ITEM_COUNT;
            DrawMenu();
        } else {
            // long press to confirm and exit menu
            SetDifficulty(current_selection);
            current_state = STATE_PLAY;
        }
    }

    previous_state = current_button;
}

void DrawGameOver() {
    LCD_Clear(0, LCD_COLOR_WHITE);
    LCD_DisplayString(60, 140, "GAME OVER");
    LCD_DisplayString(40, 180, "Hold button");
    LCD_DisplayString(45, 200, "to restart");
}

void HandleGameOverInput(void) {
    static bool previous_state = false;
    static uint32_t press_time = 0;

    bool current_button = Button_IsPressed();
    uint32_t now = HAL_GetTick();

    if (current_button && !previous_state) {
        press_time = now;
    }

    if (!current_button && previous_state) {
        uint32_t duration = now - press_time;

        if (duration >= 1000) {  // Hold to restart
            current_state = STATE_MENU;
            DrawMenu();
        }
    }

    previous_state = current_button;
}
