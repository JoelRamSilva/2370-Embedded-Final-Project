/*
 * Button_Task.c
 *
 *  Created on: Apr 9, 2025
 *      Author: joelrsilva
 */

#include "Button_Task.h"

void StartButtonTask(void const * argument){
    Button_Init();

    bool previous_state = false;
    uint32_t press_time = 0;

    // Ray gun charge bar
    int bar_x = 195;
    int bar_y_base = 55;
    int bar_spacing = 5;
    int max_bar_units = 10;

    // Double-tap tracker
    static uint32_t last_press_time = 0;

    for (;;) {
        if (current_state != STATE_PLAY) {
            osDelay(50);
            continue;
        }
        bool current_state = Button_IsPressed();
        uint32_t now = HAL_GetTick();

        // Update energy and shield system every frame
        Capacitor_Update();

        // ===== Detect Double ap to Toggle Shield =====
        if (current_state && !previous_state) {
            if (now - last_press_time <= 250) {
                printf("Double tap detected!\n");
                if (shield_active) {
                    DeactivateShield();
                } else {
                    ActivateShield();
                }
            }
            last_press_time = now;
            press_time = now;
            //printf("Button Pressed!\r\n");
            fflush(stdout);
        }

        // ===== Charging Bar  =====
        if (current_state && previous_state) {
            uint32_t held_duration = now - press_time;
            if (held_duration >= 2999){
            	held_duration = 3000;
            	FireRailgun(held_duration);
            }

            uint8_t units = (held_duration * max_bar_units) / 3000;

            for (int i = 0; i < max_bar_units; i++) {
                LCD_DisplayChar(bar_x, bar_y_base - (i * bar_spacing), ' ');
            }

            for (int i = 0; i < units; i++) {
                LCD_DisplayChar(bar_x, bar_y_base - (i * bar_spacing), '_');
            }
            //GREEN LED brightness
            uint8_t brightness = (held_duration * 100) / 12000;
            if (brightness > 100){
            	brightness = 100;  // Safety clamp
            }
            set_brightness(brightness);
        }

        // ===== Release: Fire Railgun and Consume Energy =====
        else if (!current_state && previous_state) {
            uint32_t hold_duration = now - press_time;

            if (hold_duration < 150) {
                //printf("Tap too short, WILL NOT SHOOT.\n");
            } else {
                if (hold_duration >= 3000) {
                	hold_duration = 3000;
                	FireRailgun(hold_duration);
                }

                //printf("Button Released! Hold Duration = %lu ms\r\n", hold_duration);
                // Convert hold duration to energy consumption
                uint32_t amount_to_consume = 0;
                if (hold_duration >= 2500) {
                    amount_to_consume = (MAX_CAPACITOR_ENERGY * 3) / 10;
                } else if (hold_duration >= 2000) {
                    amount_to_consume = (MAX_CAPACITOR_ENERGY * 2) / 10;
                } else {
                    amount_to_consume = (MAX_CAPACITOR_ENERGY * 1) / 10;
                }

                Capacitor_Consume(amount_to_consume);
                Capacitor_DrawBar(215, 55, 5, 10);  // show result immediately
                FireRailgun(hold_duration);


                // Clear railgun charge bar
                LCD_Clear_Rectangle(195, 20, 16, 25 * 10, LCD_COLOR_WHITE);
            }
        }

        previous_state = current_state;
        osDelay(10);
    }
}



