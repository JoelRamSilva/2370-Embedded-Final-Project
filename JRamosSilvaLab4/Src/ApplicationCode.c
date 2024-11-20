/*
 * ApplicationCode.c
 *
 *  Created on: Sep 9, 2024
 *      Author: joelrsilva
 */

#include "ApplicationCode.h"

#if DUAL_TIMER_USAGE == 0
// Timer 2 Interrupt Handler
void TIM2_IRQHandler(void) {

    if (TIM2->TIMx_SR & 0x01){
        TIM2->TIMx_SR &= ~(0x01);

        static uint8_t ledState = 0;
        if (ledState){
        	TurnOffLED(RED_LED); // Turn off the Red LED
            ledState = 0;
        }
        else{
        	TurnOnLED(RED_LED); // Turn on the Red LED for 3 seconds
            ledState = 1;

            LED_TIM2_Reset();
        }
    }
}
#endif

#if DUAL_TIMER_USAGE == 1
// Timer 5 Interrupt Handler
void TIM5_IRQHandler(void) {
    static uint8_t ledState = 0;

    // Disable interrupt
    NVIC_Toggle(TIM5_IRQ_NUMBER, DISABLE);

    // Clear the update flag
    TIM5->TIMx_SR &= ~(1 << 0);  // Clear UIF (update interrupt flag)

    // Toggle the green LED state
    ToggleLED(GREEN_LED);

    // Re-enable interrupt
    NVIC_Toggle(TIM5_IRQ_NUMBER, ENABLE);
}

// Button Interrupt Handler (for Timer 5)
void EXTI0_IRQHandler(void) {
    static uint32_t buttonHoldTime = 0;

	// Disable button interrupt in NVIC
	NVIC_Toggle(EXTI0_IRQ_NUMBER, DISABLE);

	// Check if EXTI line 0 is pending (interrupt triggered)
	if (buttonStatus()) {
		// Rising edge: button pressed, start counting
		buttonHoldTime = 0;  // Reset hold time
		LED_TIM5_Reset();
		LED_TIM5_Start();    // Start Timer 5 to track how long button is held
	}else {
			LED_TIM5_Stop();     // Stop Timer 5
			buttonHoldTime = Timer_Value(TIM5);// Get button hold duration
			LED_TIM5_ConfigAutoReload(buttonHoldTime);// Set the auto-reload to match hold time
			LED_TIM5_Reset();
			LED_TIM5_Start();
		}

		// Clear the pending flag by writing 1 to it
		EXTI->EXTI_PR |= (1 << GPIO_PIN_NUM_0);

	// Re-enable button interrupt in NVIC
    NVIC_Toggle(EXTI0_IRQ_NUMBER, ENABLE);
}
#endif

void applicationInit() {
    // Initialize and deactivate both LEDs
    redLEDInit();
    deactivateRedLED();
    greenLEDInit();
    deactivateGreenLED();

#if DUAL_TIMER_USAGE == 1
    // Timer 5: Initialize button interrupt and Timer 5
    buttonInterruptInit();
    LED_TIM5_Init();
#else
    // Timer 2: Initialize Timer 2 and start it
    LED_TIM2_Init();
    LED_TIM2_Start();
#endif
    // Ensure the delay event is still scheduled
    addSchedulerEvent(LED_DELAY_EVENT);
}



void executeButtonPollingRoutine() {
    if (buttonStatus()) {
        activateGreenLED();
    } else {
        deactivateGreenLED();
    }
}

void greenLEDInit() {
    LED_Init(GREEN_LED);
}

void redLEDInit() {
    LED_Init(RED_LED);
}

void toggleGreenLED() {
    ToggleLED(GREEN_LED);
}

void toggleRedLED() {
    ToggleLED(RED_LED);
}

void activateGreenLED() {
    TurnOnLED(GREEN_LED);
}

void activateRedLED() {
    TurnOnLED(RED_LED);
}

void deactivateGreenLED() {
    TurnOffLED(GREEN_LED);
}

void deactivateRedLED() {
    TurnOffLED(RED_LED);
}

void appDelay(uint32_t delay) {
    char firstName[NAME_LENGTH] = "Joel";
    [[maybe_unused]] char nameDestination[NAME_LENGTH] = {};

    for (int i = 0; i < delay; i++) {
        for (int j = 0; j < NAME_LENGTH; j++) {
            nameDestination[j] = firstName[j];
        }
    }
}

#if USE_INTERRUPT_FOR_BUTTON == 0
void buttonInit() {
    executeButtonPollingRoutine();
}
#elif USE_INTERRUPT_FOR_BUTTON == 1
void buttonInterruptInit() {
    button_Init_Interrup_Mode();
}
#endif








