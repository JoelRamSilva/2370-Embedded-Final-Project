/*
 * Capacitor.c
 *
 *  Created on: Apr 16, 2025
 *      Author: joelrsilva
 */


#include "Capacitor.h"
#include "LCD_Driver.h"

uint32_t capacitor_energy = MAX_CAPACITOR_ENERGY;

void Capacitor_Consume(uint32_t amount) {
    if (amount > capacitor_energy) {
        capacitor_energy = 0;
    } else {
        capacitor_energy -= amount;
    }
    //printf("Capacitor energy: %lu\n", capacitor_energy);  // ← Add this
}

void Capacitor_Set(uint32_t amount) {
    capacitor_energy = (amount > MAX_CAPACITOR_ENERGY) ? MAX_CAPACITOR_ENERGY : amount;
}

void Capacitor_Update(void) {
    static uint32_t last_charge_time = 0;
    uint32_t now = HAL_GetTick();

    // Recharge capacitor every 300 ms````
    if (now - last_charge_time >= 300) {
        if (capacitor_energy < MAX_CAPACITOR_ENERGY) {
            capacitor_energy += 60;
            if (capacitor_energy > MAX_CAPACITOR_ENERGY)
                capacitor_energy = MAX_CAPACITOR_ENERGY;
            //printf("Capacitor energy: %lu\n", capacitor_energy);
        }
        last_charge_time = now;
    }
    Capacitor_DrawBar(215, 55, 5, 10);
}


void Capacitor_DrawBar(int x, int y_base, int spacing, int max_units) {
    uint8_t units = capacitor_energy / 300;
    if (units > max_units){
    	units = max_units;
    }

    // Draw charged bars in BLACK
    for (int i = 0; i < units; i++) {
        LCD_DisplayCharColored(x, y_base - (i * spacing), '_', LCD_COLOR_BLACK);
    }

    // Draw the depleted bars in WHITE
    for (int i = units; i < max_units; i++) {
        LCD_DisplayCharColored(x, y_base - (i * spacing), '_', LCD_COLOR_WHITE);
    }
}










