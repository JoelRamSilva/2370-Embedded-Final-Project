/*
 * Railgun.h
 *
 *  Created on: Apr 14, 2025
 *      Author: joelrsilva
 */

#ifndef INC_RAILGUN_H_
#define INC_RAILGUN_H_


#include <stdint.h>
#include "LCD_Driver.h"
#include "cmsis_os.h"
#include "Capacitor.h"

#include <stdio.h>
#include <stdbool.h>

#define GRAVITY 1.f
#define GROUND_Y 260
#define LEFT_BOUNDARY 40
#define TOP_BOUNDARY 10
#define RIGHT_BOUNDARY LCD_PIXEL_WIDTH

typedef struct {
    float x, y;
    float vx, vy;
    bool active;
} RailgunProjectile;

extern RailgunProjectile projectile;
extern uint32_t railgun_energy;

void FireRailgun(uint32_t power_ms);
void Railgun_Update(void);

#endif /* INC_RAILGUN_H_ */
