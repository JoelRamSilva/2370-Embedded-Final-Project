/*
 * Button_Drive.c
 *
 *  Created on: Sep 26, 2024
 *      Author: joelrsilva
 */

#include <Button_Drive.h>
#include <stm32f4xx_hal.h>


void buttonInit(){
	GPIO_InitTypeDef GPIO_InitButton = {0};

	buttonClock();

	GPIO_InitButton.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitButton.Pin = GPIO_PIN_0;
	GPIO_InitButton.Speed = GPIO_SPEED_LOW;
	GPIO_InitButton.Pull = GPIO_MODE_OUTPUT_PP;

	HAL_GPIO_Init(GPIOA, &GPIO_InitButton);
}

void buttonClock(){
	__HAL_RCC_GPIOA_CLK_ENABLE();
}

bool buttonStatus(){

	if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == BUTTON_PRESSED){
		return true;
	}
	else{
		return false;
	}
}

void button_Init_Interrup_Mode(){
	GPIO_InitTypeDef GPIO_InitInterruptButton = {0};
	buttonClock();

	GPIO_InitInterruptButton.Mode = GPIO_MODE_IT_RISING_FALLING;
	GPIO_InitInterruptButton.Pin = GPIO_PIN_0;
	GPIO_InitInterruptButton.Speed = GPIO_SPEED_LOW;
	GPIO_InitInterruptButton.Pull = GPIO_NOPULL;

	HAL_GPIO_Init(GPIOA, &GPIO_InitInterruptButton);
    //HAL_NVIC_SetPriority(EXTI0_IRQn, 5, 0);  // make it a priority
    HAL_NVIC_EnableIRQ(EXTI0_IRQn);          // enable interrupt
}
