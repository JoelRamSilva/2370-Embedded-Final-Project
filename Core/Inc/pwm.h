/*
 * pwm.h
 *
 *  Created on: Apr 28, 2025
 *      Author: joelrsilva
 */
#include <stdint.h>

#ifndef INC_PWM_H_
#define INC_PWM_H_

#define NVIC_ISER0      (*(volatile uint32_t *)(0xE000E100))

// RCC registers
typedef struct {
    volatile uint32_t CR;
    volatile uint32_t PLLCFGR;
    volatile uint32_t CFGR;
    volatile uint32_t CIR;
    volatile uint32_t AHB1RSTR;
    volatile uint32_t AHB2RSTR;
    uint32_t RESERVED1[2];
    volatile uint32_t APB1RSTR;
    volatile uint32_t APB2RSTR;
    uint32_t RESERVED2[2];
    volatile uint32_t AHB1ENR;
    volatile uint32_t AHB2ENR;
    uint32_t RESERVED3[2];
    volatile uint32_t APB1ENR;
    volatile uint32_t APB2ENR;
} RCC_TypeDef;
#define RCC ((RCC_TypeDef *)0x40023800)

// GPIO registers
typedef struct {
    volatile uint32_t MODER;
    volatile uint32_t OTYPER;
    volatile uint32_t OSPEEDR;
    volatile uint32_t PUPDR;
    volatile uint32_t IDR;
    volatile uint32_t ODR;
    volatile uint32_t BSRR;
    volatile uint32_t LCKR;
    volatile uint32_t AFR[2];
} GPIO_TypeDef;
#define GPIOG ((GPIO_TypeDef *)0x40021800)

// Timer Registers Structure
typedef struct {
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t SMCR;
    volatile uint32_t DIER;
    volatile uint32_t SR;
    volatile uint32_t EGR;
    volatile uint32_t CCMR1;
    volatile uint32_t CCMR2;
    volatile uint32_t CCER;
    volatile uint32_t CNT;
    volatile uint32_t PSC;
    volatile uint32_t ARR;
} TIM2_TypeDef;
#define TIM2 ((TIM2_TypeDef *)0x40000000)

#define LED_PIN 13
#define LED_ON()  (GPIOG->ODR |= (1U << LED_PIN))
#define LED_OFF() (GPIOG->ODR &= ~(1U << LED_PIN))

#define RED_LED_PIN 14
#define RED_LED_ON()  (GPIOG->ODR |= (1U << RED_LED_PIN))
#define RED_LED_OFF() (GPIOG->ODR &= ~(1U << RED_LED_PIN))


void TIM2_Init(void);
void GPIO_Init(void);
void TIM2_IRQHandler(void);
void set_brightness(uint8_t brightness);

#endif /* INC_PWM_H_ */
