/*
 * Display_Task.h
 *
 *  Created on: Apr 9, 2025
 *      Author: joelrsilva
 */
#include "Shield.h"
#include "Main_Menu.h"
#include "Capacitor.h"
#include "LCD_Driver.h"
#include "Button_Task.h"
#include "Shield.h"
#include "Capacitor.h"
#include "fonts.h"
#include "cmsis_os.h"
#include "Gyro_Driver.h"
#include "Enemy.h"
#include "Collision.h"
#include <stdio.h>

#ifndef INC_DISPLAY_TASK_H_
#define INC_DISPLAY_TASK_H_

void StartDisplayTask(void const * argument);
void drawCastleAndCliff();
void drawCannonAndPlatform(int platform_x, int platform_y, uint16_t color);
void movePlatformWithGyro(int* platform_x);
extern void PrisonerEscapeAnimation(void);
#endif /* INC_DISPLAY_TASK_H_ */

