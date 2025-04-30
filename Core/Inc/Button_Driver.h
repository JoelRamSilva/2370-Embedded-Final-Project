/*
 * Button_Driver.h
 *
 *  Created on: Apr 9, 2025
 *      Author: joelrsilva
 */

#ifndef INC_BUTTON_DRIVER_H_
#define INC_BUTTON_DRIVER_H_

#include "stm32f4xx_hal.h"
#include <stdbool.h>
#include <stdio.h>



#define BUTTON_GPIO_PORT GPIOA
#define BUTTON_PIN GPIO_PIN_0


void Button_Init(void);
bool Button_IsPressed(void);

#endif /* INC_BUTTON_DRIVER_H_ */
