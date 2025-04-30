/*
 * Collision.c
 *
 *  Created on: Apr 17, 2025
 *      Author: joelrsilva
 */

#include "Collision.h"
#include "Enemy.h"


extern GameState current_state;
extern RailgunProjectile projectile;


static int cliff_hit_count = 0;
static bool castle_hit = false;
bool prisoners_escaping = false;
static uint32_t escape_start_time = 0;
static uint32_t last_blink_time = 0;
static bool red_led_on = false;

//=======WALL COLLISION==========
#define CANYON_LEFT_WALL_X      10
#define CANYON_RIGHT_WALL_X     210
#define WALL_IMPACT_DEATH_SPEED 30.0f

//void StartCollisionTask(void const * argument) {
//    while (1) {
//        //printf("Collision task running\n");  // Confirm this task is active
//        HandleCollisions(platform_x);
//        //osDelay(50);  // Temporarily slow it down for visibility
//    }
//}

bool SatchelHitsPlatform(float satchel_x, float satchel_y, int platform_x) {
    float platform_left = platform_x;
    float platform_right = platform_x + PLATFORM_WIDTH;
    float platform_top = PLATFORM_Y;

    return (
        satchel_y >= platform_top &&
        satchel_y <= platform_top + PLATFORM_HEIGHT &&
        satchel_x >= platform_left &&
        satchel_x <= platform_right
    );
}




bool SatchelHitsShield(float satchel_x, float satchel_y, int platform_x) {
    float shield_center_x = platform_x + 30;
    float shield_radius = 40;  // Adjust as needed

    float dx = satchel_x - shield_center_x;
    float dy = satchel_y - PLATFORM_Y;

    return (dx * dx + dy * dy <= shield_radius * shield_radius);
}

bool RailgunHitsSatchel(float x, float y) {
   //big maybe
    return false;
}


void HandleCollisions(int platform_x) {
//    static int cliff_hit_count = 0;
//    static bool castle_hit = false;
//    static bool prisoners_escaping = false;
//    static uint32_t escape_start_time = 0;

    // === Handle prisoners escaping RED LED blinking ===
    if (prisoners_escaping) {
        uint32_t now = HAL_GetTick();
        //PrisonerEscapeAnimation();

        // blink  red LED every 300ms
        if (now - last_blink_time >= 300) {
            last_blink_time = now;

            if (red_led_on) {
                RED_LED_OFF();
                red_led_on = false;
            } else {
                RED_LED_ON();
                red_led_on = true;
            }
        }

        // If 5 seconds passed, WIN the game
        if (now - escape_start_time >= 5000) {
            RED_LED_OFF();
            prisoners_escaping = false;
            Game_Win();
        }
    }

    // === Satchel/enemy bullet collision  ===
    for (int i = 0; i < MAX_SATCHELS; i++) {
        if (!satchels[i].active) continue;

        if (shield_active && SatchelHitsShield(satchels[i].x, satchels[i].y, platform_x)) {
            //printf("Satchel %d hit the shield at (%d, %d)\n", i, (int)satchels[i].x, (int)satchels[i].y);
            satchels[i].active = false;
            Shield_TakeHit();
        } else if (SatchelHitsPlatform(satchels[i].x, satchels[i].y, platform_x)) {
            //printf("Satchel %d hit the platform at (%d, %d)\n", i, (int)satchels[i].x, (int)satchels[i].y);
            satchels[i].active = false;
            Game_Lose();
        }
    }

    // === Slug/bullet collision ===
    if (projectile.active) {
        // 1. Self-hit check
        if (projectile.y >= 255 &&
            projectile.x >= platform_x &&
            projectile.x <= platform_x + PLATFORM_WIDTH) {

            //printf("Slug hit yourself at (%d, %d)\n", (int)projectile.x, (int)projectile.y);
            projectile.active = false;

            if (shield_active) {
                if (GetShieldHealth() > (SHIELD_MAX_HEALTH / 3)) {
                    for (int j = 0; j < (SHIELD_MAX_HEALTH / 3); j++) {
                        Shield_TakeHit();
                    }
                } else {
                    Game_Lose();
                }
            } else {
                Game_Lose();
            }
            return;
        }

        // Castle hit (start escape immediately)
        if (projectile.y <= CASTLE_BOTTOM && projectile.x <= CASTLE_RIGHT) {
            //printf("Slug hit the castle at (%d, %d)\n", (int)projectile.x, (int)projectile.y);
            projectile.active = false;

            if (!prisoners_escaping) {  // Only if not already escaping
                prisoners_escaping = true;
                escape_start_time = HAL_GetTick();
                RED_LED_ON();
            } else {
                // If they are already escaping, shooting again than lose
                Game_Lose();
            }
            return;
        }

        // 3. Cliff hit (after 2nd hit, start escape)
        if (projectile.y >= HIGH_CLIFF_TOP &&
            projectile.x <= HIGH_CLIFF_RIGHT &&
            projectile.y <= HIGH_CLIFF_BOTTOM) {

            projectile.active = false;
            cliff_hit_count++;
            //printf("Slug hit the cliff! Total hits = %d\n", cliff_hit_count);

            if (cliff_hit_count >= 2 && !prisoners_escaping) {
                prisoners_escaping = true;
                escape_start_time = HAL_GetTick();
                RED_LED_ON();
            }
            return;
        }
    }
}



void Game_Lose() {
    current_state = STATE_GAME_OVER;
    DrawGameOver();
}

void Game_Win() {
    current_state = STATE_GAME_OVER;
    LCD_Clear(0, LCD_COLOR_WHITE);
    LCD_DisplayString(50, 120, "YOU WIN!");
}


void CheckPlatformWallCollision(float* pos_x, float* vel_x, float width)
{
    if (*pos_x <= CANYON_LEFT_WALL_X || (*pos_x + width) >= CANYON_RIGHT_WALL_X)
    {
        if (fabsf(*vel_x) > WALL_IMPACT_DEATH_SPEED)
        {
            printf("Crashed into wall! Velocity: %d\n", (int)(*vel_x));
            Game_Lose();
        }
        else
        {
            *vel_x = -*vel_x;  // Bouncy

            if (*pos_x <= CANYON_LEFT_WALL_X)
                *pos_x = CANYON_LEFT_WALL_X + 1;
            else
                *pos_x = CANYON_RIGHT_WALL_X - width - 1;
        }
    }
}


