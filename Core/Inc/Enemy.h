/*
 * Enemy.h
 *
 *  Created on: Apr 16, 2025
 *      Author: joelrsilva
 */

#ifndef INC_ENEMY_H_
#define INC_ENEMY_H_

#include "LCD_Driver.h"
#include "Difficulty.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define MAX_SATCHELS 3  // Only 1 will be used in Easy, more in harder modes
#define ENEMY_GRAVITY_MIN 0.1f
#define ENEMY_GRAVITY_MAX 0.2f

typedef struct {
    float x, y;
    float vx, vy;
    bool active;
} Satchel;

extern Satchel satchels[MAX_SATCHELS];



bool SatchelIsActive();
void SpawnSatchel(void);
void UpdateSatchels(void);
void ResetSatchels(void);

#endif /* INC_ENEMY_H_ */

