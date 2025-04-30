/*
 * Railgun.c
 *
 *  Created on: Apr 14, 2025
 *      Author: joelrsilva
 */


#include "Railgun.h"


extern int platform_x;
uint32_t railgun_energy = 50000;  // Initial energy for railgun
RailgunProjectile projectile = {0};  // global instance

static bool prisoners_escaping = false;
static uint32_t escape_start_time = 0;

void FireRailgun(uint32_t power_ms) {
	uint32_t energy_cost = power_ms / 100;

    if (projectile.active){
    	return;  // Only one active projectile at a time
    }
    else if (capacitor_energy < energy_cost || projectile.active) {
        return;
    }

    // Clamp input duration between 300 and 3000 ms
    if (power_ms < 300){
    	power_ms = 300;
    }
    if (power_ms > 3000){
    	power_ms = 3000;
    }

    // sXale velocity based on power input
    float velocity = (power_ms - 300) * (30.0f / (3000.0f - 300.0f));  // maps 300ms → 0, 3000ms → 30


    // printf("Power: %lu → Velocity: %.2f\n", power_ms, velocity);
    projectile.x = platform_x + 30;
    projectile.y = 236;

    projectile.vx = -velocity * 0.5f;  // arc to the left
    projectile.vy = -velocity;         // upward force

    projectile.active = true;



    railgun_energy -= (power_ms / 100);


}

void Railgun_Update(void) {
    if (!projectile.active) {
    	return;
    }

    //Bullets current position
    int prev_x = (int)projectile.x;
    int prev_y = (int)projectile.y;

    // Update physics  ========BOT X and Y positioning
    projectile.vy += GRAVITY;
    projectile.x += projectile.vx;
    projectile.y += projectile.vy;

    // Clear previous pixel
    LCD_Draw_Circle_Fill(prev_x, prev_y, 2, LCD_COLOR_WHITE);

    if (projectile.y >= GROUND_Y ||
    	(projectile.y <= GROUND_Y && projectile.x <= LEFT_BOUNDARY)||
		(projectile.y <= 150 && projectile.x <= 80)) {

        projectile.active = false;
        set_brightness(0);
        return;
    }

    // Draw new pixel
    LCD_Draw_Circle_Fill((int)projectile.x, (int)projectile.y, 2, LCD_COLOR_BLUE);

}



