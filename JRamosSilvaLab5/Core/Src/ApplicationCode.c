/*
 * ApplicationCode.c
 *
 *  Created on: Sep 9, 2024
 *      Author: joelrsilva
 */

#include "ApplicationCode.h"

void applicationInit(){
//	 greenLEDInit();
//	 deactivateGreenLED();
// 	 executeButtonPollingRoutine();

#if	USE_INTERRUPT_FOR_BUTTON
	 buttonInterruptInit();

#elif USE_INTERRUPT_FOR_BUTTON == 0 //check if it is set to 0
	 buttonInit();
	 addSchedulerEvent(BUTTON_POOL_EVENT);
#endif
	 addSchedulerEvent(LED_DELAY_EVENT);
}


void executeButtonPollingRoutine(){
	 if (buttonStatus()){
		 activateGreenLED();
	 }
	 else{
		 deactivateGreenLED();
	 }
}

void greenLEDInit(){
	 LED_Init(GREEN_LED);
}

void redLEDInit(){
	 LED_Init(RED_LED);
}

void toggleGreenLED(){
	ToggleLED(GREEN_LED);
}

void toggleRedLED(){
	ToggleLED(RED_LED);
}

void activateGreenLED(){
	TurnOnLED(GREEN_LED);
}

void activateRedLED(){
	TurnOnLED(RED_LED);
}

void deactivateGreenLED(){
	TurnOffLED(GREEN_LED);
}

void deactivateRedLED(){
	TurnOffLED(RED_LED);
}

void appDelay(uint32_t delay){
	char firstName[NAME_LENGTH] = "Joel";
	[[maybe_unused]]char nameDestination[NAME_LENGTH] = {};

	for (int i = 0; i < DEFAULT_DELAY; i++){
		for (int j = 0; j < NAME_LENGTH; j++){
			nameDestination[j] = firstName[j];
		}
	}
}

void Application_InitGyro() {
    Gyro_Init();
    Gyro_PowerOn();
    Gyro_RegisterConfigure();
}


void Application_PrintGyroDeviceID() {
    Gyro_DeviceIDPrint();
}


void Application_PrintGyroTemperature() {
    Gyro_TemperaturePrint();
}


void Application_ConfigureGyro() {
    Gyro_RegisterConfigure();
}



//--------------------VERIFY THE CODE-----------
void EXTI0_IRQHandler() {
	HAL_NVIC_DisableIRQ(EXTI0_IRQn);
    addSchedulerEvent(DEVICE_ID_AND_TEMP_EVENT);
    EXTI_Clear_Pending(BUTTON_PIN);
    HAL_NVIC_ClearPendingIRQ(EXTI0_IRQn);
    HAL_NVIC_EnableIRQ(EXTI0_IRQn);
}


#if USE_INTERRUPT_FOR_BUTTON == 0
void buttonInit(){
	executeButtonPollingRoutine();
}
#elif USE_INTERRUPT_FOR_BUTTON == 1
void buttonInterruptInit(){
	button_Init_Interrup_Mode();
}
#endif


