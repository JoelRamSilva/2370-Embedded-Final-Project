

#ifndef APPLICATIONCODE_H_
#define APPLICATIONCODE_H_

#define NAME_LENGTH 5
#define DEFAULT_VAL 250000
#define DAUL_TIMER_USAGE 1

#include <stdio.h>
#include <stdint.h>
#include <LED_Driver.h>
#include <STM32F429i.h>
#include <scheduler.h>
#include <GPIO_Driver.h>
#include <ButtonDriver.h>

#define USE_INTERRUPT_FOR_BUTTON 1

void Application_Init();

//START
void GreenInt();
void RedInt();
void BothInt();

//TOGGLE
void GreenToggle();
void RedToggle();

//ON
void GreenOn();
void RedOn();

//OFF
void GreenOff();
void RedOff();

#ifdef USE_INTERRUPT_FOR_BUTTON
void Application_ButtonInitInterruptMode();
#else
void Application_ButtonInit();
void executeButtonPollingRoutine();
#endif

void delayProto(uint32_t timeDelay);

#endif /* APPLICATIONCODE_H_ */
