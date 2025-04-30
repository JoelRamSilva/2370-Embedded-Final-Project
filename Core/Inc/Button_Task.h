/*
 * Button_Task.h
 *
 *  Created on: Apr 9, 2025
 *      Author: joelrsilva
 */
#include "Button_Driver.h"
#include "Main_Menu.h"
#include "cmsis_os.h"
#include "Railgun.h"
#include "LCD_Driver.h"
#include "Shield.h"
#include "Capacitor.h"
#include <stdio.h>

#include <stdbool.h>


#ifndef INC_BUTTON_TASK_H_
#define INC_BUTTON_TASK_H_

#define MAX_RAILGUN_CHARGE_TIME 3000

void StartButtonTask(void const * argument);
void UpdateEnergyBar(int x, int y, uint32_t energy, int max_units, int unit_height);

#endif /* INC_BUTTON_TASK_H_ */
