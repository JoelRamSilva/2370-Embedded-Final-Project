/*
 * Enemy.c
 *
 *  Created on: Apr 16, 2025
 *      Author: joelrsilva
 */


#include "Enemy.h"

Satchel satchels[MAX_SATCHELS];
Satchel satchel = { .active = false };
float satchel_gravity = 1.0f;

bool SatchelIsActive() {
	return satchel.active && satchel.y < 270;
}

void ResetSatchels(void) {
    for (int i = 0; i < MAX_SATCHELS; i++) {
        satchels[i].active = false;
    }
}

void SpawnSatchel() {
    int active_count = 0;
    for (int i = 0; i < MAX_SATCHELS; i++) {
        if (satchels[i].active) {
            active_count++;
        }
    }

    if (active_count >= GetMaxSatchels()) {
        return;
    }

    for (int i = 0; i < MAX_SATCHELS; i++) {
        if (!satchels[i].active) {
            satchels[i].x = 50;
            satchels[i].y = 140;

            // Randomize vx between 1–7, vy between -4–-8 (upward)
            float vx = 1.0f + ((rand() % 100) / 100.0f) * 5.0f;  // 1.0 → 7.0
            float vy = -(1.0f + ((rand() % 100) / 100.0f) * 4.0f);  // -1.0 → -5.0 (up)

            satchel_gravity = ENEMY_GRAVITY_MIN + ((rand() % 100) / 100.0f) * (ENEMY_GRAVITY_MAX - ENEMY_GRAVITY_MIN);

            satchels[i].vx = vx;
            satchels[i].vy = vy;
            satchels[i].active = true;
            break;
        }
    }
}



void UpdateSatchels() {
	fflush(stdout);
    bool any_active = false;
    for (int i = 0; i < MAX_SATCHELS; i++) {
        if (!satchels[i].active) continue;
        any_active = true;
        // Satchel physics update
        LCD_Draw_Circle_Fill((int)satchels[i].x, (int)satchels[i].y, 3, LCD_COLOR_WHITE);
        satchels[i].vy += satchel_gravity;
        satchels[i].y += satchels[i].vy;
        satchels[i].x += satchels[i].vx;
        if (satchels[i].y >= 280 || satchels[i].x >= 235) {
            satchels[i].active = false;
        } else {
            LCD_Draw_Circle_Fill((int)satchels[i].x, (int)satchels[i].y, 3, LCD_COLOR_RED);
        }
    }
    if (!any_active) {
        //printf("No active satchels right now.\n");
    }
}



