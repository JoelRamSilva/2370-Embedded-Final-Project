/*
 * Shield.c
 *
 *  Created on: Apr 15, 2025
 *      Author: joelrsilva
 */

#include "Shield.h"
#include "Capacitor.h"
#include "LCD_Driver.h"
#include <stdio.h>

bool shield_active = false;

static uint8_t shield_health = SHIELD_MAX_HEALTH;
uint8_t previous_health_for_update = SHIELD_MAX_HEALTH;

static uint32_t last_drain_time = 0;


void StartShieldTask(void const * argument) {
    for (;;) {
        Shield_Update();
        osDelay(10);
    }
}



void ActivateShield(void) {
    if (!shield_active && capacitor_energy >= SHIELD_BAR_COST) {
        shield_active = true;
        last_drain_time = HAL_GetTick();
        shield_health = SHIELD_MAX_HEALTH;

        printf("Shield Activated!\n");

        // Draw full health bar in BLACK
        int bar_x = 175;
        int bar_y_base = 55;
        int bar_spacing = 5;
        for (int i = 0; i < SHIELD_MAX_HEALTH; i++) {
            LCD_DisplayCharColored(bar_x, bar_y_base - (i * bar_spacing), '_', LCD_COLOR_BLACK);
        }
    }
}


void DeactivateShield(void) {
    if (shield_active) {
        shield_active = false;
        printf("Shield Deactivated!\n");

        // Clear shield bar
        LCD_Clear_Rectangle(175, 20, 16, 25 * 10, LCD_COLOR_WHITE);
    }
}



void Shield_TakeHit(void) {
    if (shield_active && shield_health > 0) {
        uint8_t previous_health = shield_health;

        // Deduct 5 health
        if (shield_health >= SHIELD_DAMAGE) {
            shield_health -= SHIELD_DAMAGE;
        } else {
            shield_health = 0;
        }

        printf("Shield took damage! Health: %d\n", shield_health);

        // Draw white bars for lost health
        int bar_x = 175;
        int bar_y_base = 55;
        int bar_spacing = 5;

        for (int i = shield_health; i < previous_health; i++) {
            LCD_DisplayCharColored(bar_x, bar_y_base - (i * bar_spacing), '_', LCD_COLOR_WHITE);
        }

        // Deactivate if health reaches 0
        if (shield_health == 0) {
            printf("Shield destroyed by damage!\n");
            DeactivateShield();
        }
    }
}





uint8_t GetShieldHealth(void) {
    return shield_health;
}

void Shield_Update(void) {
    static uint32_t last_update_time = 0;
    static uint8_t previous_health = SHIELD_MAX_HEALTH;
    uint32_t now = HAL_GetTick();

    if (!shield_active) return;

    // Limit how often this runs to reduce LCD flicker & CPU load
    if (now - last_update_time < 10) return;
    last_update_time = now;

    // === Drain capacitor energy ===
    if (now - last_drain_time >= SHIELD_DRAIN_INTERVAL) {
        if (capacitor_energy >= SHIELD_BAR_COST) {
            Capacitor_Consume(SHIELD_BAR_COST);
            Capacitor_DrawBar(215, 55, 5, 10);   // Show energy after drain
            last_drain_time = now;
        } else {
            printf("Shield deactivated: not enough capacitor energy.\n");
            DeactivateShield();
            return;
        }
    }

    // === Shield Bar Update ===
    int bar_x = 175;
    int bar_y_base = 55;
    int bar_spacing = 5;

    if (shield_health < previous_health) {
        // Erase ONLY the lost health units with white '_'
        for (int i = shield_health; i < previous_health; i++) {
            LCD_DisplayCharColored(bar_x, bar_y_base - (i * bar_spacing), '_', LCD_COLOR_WHITE);
        }
        previous_health = shield_health;
    }
}




