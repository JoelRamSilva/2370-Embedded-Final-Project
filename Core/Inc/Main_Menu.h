/*
 * Main_Menu.h
 *
 *  Created on: Apr 16, 2025
 *      Author: joelrsilva
 */

#ifndef INC_MAIN_MENU_H_
#define INC_MAIN_MENU_H_

#include "Difficulty.h"
#include "LCD_Driver.h"
#include "Button_Driver.h"
#include "Gyro_Driver.h"
#include "stm32f4xx_hal.h"
#include <stdbool.h>

#define MENU_ITEM_COUNT 3

typedef enum {
    STATE_MENU,
    STATE_PLAY,
    STATE_PAUSE,
    STATE_GAME_OVER
} GameState;

extern GameState current_state;

void DrawMenu(void);
void HandleMenuInput(void);

void DrawGameOver();
void HandleGameOverInput(void);

#endif /* INC_MAIN_MENU_H_ */
