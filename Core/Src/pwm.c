/*
 * pwm.c
 *
 *  Created on: Apr 28, 2025
 *      Author: joelrsilva
 */

#include "pwm.h"

uint8_t duty_cycle = 0; // Start at 50% brightness
uint8_t pwm_counter = 0;

void GPIO_Init(void) {
    // Enable GPIOG clock
    RCC->AHB1ENR |= (1U << 6);

    // PG13 and PG14 as output
    GPIOG->MODER &= ~((3U << (13 * 2)) | (3U << (14 * 2)));
    GPIOG->MODER |=  ((1U << (13 * 2)) | (1U << (14 * 2)));


}

void TIM2_Init(void) {
    // Enable TIM2 clock
    RCC->APB1ENR |= (1U << 0);

    // Configure Timer 2 for 20 kHz PWM
    TIM2->PSC = 8 - 1;   // Clock = 16MHz / 8 = 2MHz
    TIM2->ARR = 100 - 1; // 2MHz / 100 = 20 kHz
    /**
     * You can change the prescaler value and the ARR value if you want,
     * just make sure the frequency is fast enough that you can't see it blinking.
     */

    // Enable update interrupt
    TIM2->DIER |= (1U << 0);
    NVIC_ISER0 |= (1U << 28); // IRQ number for TIM2 is 28

    // Start timer
    TIM2->CR1 |= (1U << 0);
}

void TIM2_IRQHandler(void) {
    if (TIM2->SR & (1U << 0)) {  // Check for update interrupt
        TIM2->SR &= ~(1U << 0);  // Clear interrupt flag
        pwm_counter++;

        if (pwm_counter >= 100)
            pwm_counter = 0;

        if (pwm_counter < duty_cycle) {
            LED_ON();
        } else {
            LED_OFF();
        }
    }
}

void set_brightness(uint8_t brightness) {
    if (brightness > 100) {
        brightness = 100;  // Ensure brightness is within range
    }
    duty_cycle = brightness;  // Set the desired brightness
}
