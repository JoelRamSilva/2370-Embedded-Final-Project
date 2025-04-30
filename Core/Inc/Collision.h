/*
 * Colision.h
 *
 *  Created on: Apr 17, 2025
 *      Author: joelrsilva
 */

#ifndef INC_COLLISION_H_
#define INC_COLLISION_H_

#include "Display_Task.h"
#include "Shield.h"
#include "Railgun.h"
#include "Collision.h"
#include "Main_Menu.h"
#include "Enemy.h"
#include <stdbool.h>
#include <math.h>
#include <stdio.h>
//#include <pwm.h>
#include "cmsis_os.h"


// Platform dimensions
#define PLATFORM_Y 260
#define PLATFORM_HEIGHT 10
#define PLATFORM_WIDTH 60
#define PLATFORM_X_OFFSET 0

//castle and cliff  hitbox
#define CASTLE_RIGHT 92
#define CASTLE_BOTTOM 90

#define HIGH_CLIFF_RIGHT 95
#define HIGH_CLIFF_TOP 91
#define HIGH_CLIFF_BOTTOM 145



#define RED_LED_PIN 14
#define RED_LED_ON()  (GPIOG->ODR |= (1U << RED_LED_PIN))
#define RED_LED_OFF() (GPIOG->ODR &= ~(1U << RED_LED_PIN))

extern int platform_x;
extern bool prisoners_escaping;



void StartCollisionTask(void const * argument);
void Game_Lose();

bool RailgunHitsSatchel(float x, float y);
void HandleCollisions(int platform_x);

bool SatchelHitsPlatform(float satchel_x, float satchel_y, int platform_x);
bool SatchelHitsShield(float satchel_x, float satchel_y, int platform_x);

void CheckPlatformWallCollision(float* pos_x, float* vel_x, float width);

#endif /* INC_COLLISION_H_ */
