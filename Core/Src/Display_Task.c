/*
 * Display_Task.c
 *
 *  Created on: Apr 9, 2025
 *      Author: joelrsilva
 */

#include "Display_Task.h"


#define MAX_VELOCITY 100       // Maximum platform velocity (pixels per update)
#define FRICTION 2             // Friction to slow down
#define ACCELERATION 7        // Adjusted acceleration due with gyro input (smaller value = slower movement)
#define BOUNCE_DAMPING 0.9    // Damping factor when bouncy off walls
#define DEADZONE 10            // Deadzone for gyro input (adjust as needed)
#define SCALE_FACTOR 400      // Scaling factor to reduce the sensitivity of the gyro input

static int platform_velocity = 0;  // Current velocity of the platform (pixels per update)
static int platform_acceleration = 0;  // Platform's current acceleration (change in velocity)
int platform_x = 40;  // Starting position of the platform

const char* castle_and_cliff[] = {
"  ] ^ ",
"::|/_\\ ",
"[]|::|",
":: ::|",
":#:|x|",
"^^^^^^\\",
"  .  _/",
": _/",
" _/",
"   ",
"   ",
"   ",
"   ",
"   ",
"    ~  ~  ~ ~ ",
"~ ~ ~  ~   ~ ~ ~"
};


void StartDisplayTask(void const * argument) {

    //int platform_x = 100; //Start of the cliff
    LCD_Clear(0, LCD_COLOR_WHITE);
	DrawMenu();
//    while (current_state == STATE_MENU) {
//        //printf("In menu loop\n");
//        HandleMenuInput();
//        osDelay(50);
//    }
//    LCD_Clear(0, LCD_COLOR_BLUE);
//    osDelay(100);
//    LCD_Clear(0, LCD_COLOR_RED);
//    osDelay(100);
//    LCD_Clear(0, LCD_COLOR_WHITE);
//    osDelay(50);
    int platform_y = 260;

    osDelay(50);
    GameState previous_state = STATE_MENU;
    while (1) {
        if (current_state != previous_state) {

            if (current_state == STATE_PLAY) {
                LCD_Clear(0, LCD_COLOR_WHITE);
                // ===Shield Gun Energy
                LCD_DisplayChar(175, 1, 'S');
                LCD_DisplayChar(195, 1, 'G');
                LCD_DisplayChar(214, 1, 'E');
                drawCastleAndCliff();
            }
            previous_state = current_state;
        }

        switch (current_state) {

        case STATE_PLAY:
            movePlatformWithGyro(&platform_x);
            Railgun_Update();
            UpdateSatchels();
            HandleCollisions(platform_x);
            if (prisoners_escaping) {
                PrisonerEscapeAnimation();
            }

            if (shield_active) {
                drawCannonAndPlatform(platform_x, platform_y, LCD_COLOR_BLUE);
            } else {
                drawCannonAndPlatform(platform_x, platform_y, LCD_COLOR_BLACK);
            }

            if (!SatchelIsActive()) {
                SpawnSatchel();
            }
            break;

         case STATE_MENU:
                HandleMenuInput();
                break;

         case STATE_GAME_OVER:
                HandleGameOverInput();
                break;

            default:
                break;
        }

        osDelay(50);
    }
}

void drawCastleAndCliff() {
    int y = 0;
    int line_height = 20;
    int x_offset = 0;

    // Loop through the castle charactr array till hit NULL !!!!MIGHT CHANGE TO CHARACTER BASED!!!!!
    while (castle_and_cliff[y] != NULL) {
        //Reducce the display offset
    	LCD_DisplayString(x_offset, y * line_height, (char*)castle_and_cliff[y]);
        y++;
    }
}

void drawCannonAndPlatform(int platform_x, int platform_y, uint16_t color) {
    static int prev_platform_x = -1;  // Track previous position to clear old platform

    // Only clear if the platform has moved
    if (platform_x != prev_platform_x && prev_platform_x != -1) {
        // Clear the old platform: platform is drawn in a 6-character lenght (60px wide)

        // Clear platform left part
        if (prev_platform_x > 30) {
            LCD_Clear_Rectangle(prev_platform_x, platform_y, 40, 20, LCD_COLOR_WHITE); // Clear the left side
        }

        // Clear platform right part
        uint16_t right_start = prev_platform_x + 60;
        if (right_start < LCD_PIXEL_WIDTH) {
            LCD_Clear_Rectangle(right_start, platform_y, LCD_PIXEL_WIDTH - right_start, 20, LCD_COLOR_WHITE);  // Clear the right side
        }

        // Clear the old cannon (fixed position relative to the platform)
        int prev_cannon_x = prev_platform_x + 25;
        LCD_Clear_Rectangle(prev_cannon_x, 236, 20, 24, LCD_COLOR_WHITE);  // Top cannon part
        LCD_Clear_Rectangle(prev_cannon_x, 250, 30, 24, LCD_COLOR_WHITE);  // Bottom cannon part
    }

    // platform limiters
    if (platform_x < 10) {
        platform_x = 10;
    }
    if (platform_x > LCD_PIXEL_WIDTH - 65) {  // Assuming platform is 60px wide (6 * 10px per char)
        platform_x = LCD_PIXEL_WIDTH - 65;
    }

    // Draw the new platform and cannon at updated position
    int cannon_x = platform_x + 20;   // Center the cannon
    int cannon_y_top = 236;           // Top part
    int cannon_y_bottom = 250;        // Bottom part

    // Draw the platform (6 '=' characters 10px apart)
    for (int i = 0; i < 5; i++) {
        LCD_DisplayCharColored(platform_x + i * 10, platform_y, '=', color);
    }

    // Draw the cannon
    // Top: "\\"
    LCD_DisplayCharColored(cannon_x + 1, cannon_y_top, '\\', color);
    LCD_DisplayCharColored(cannon_x + 6, cannon_y_top, '\\', color);

    // Bottom: "/\\"
    LCD_DisplayCharColored(cannon_x, cannon_y_bottom, '/', color);
    LCD_DisplayCharColored(cannon_x + 6, cannon_y_bottom, '\\', color);
    LCD_DisplayCharColored(cannon_x + 11, cannon_y_bottom, '\\', color);

    // Save the current platform_x for the next iteration
    prev_platform_x = platform_x;
    osDelay(50);
}

void movePlatformWithGyro(int* platform_x) {
    static int prev_gyro_y = 0;   // Previous gyro value for smoothing
    int gyro_y_velocity = Gyro_Get_Velocity();  // Get current gyro Y velocity

    // Simple moving average filter for smoothing gyro input
    int filtered_gyro_y = (prev_gyro_y + gyro_y_velocity) / 2;
    prev_gyro_y = filtered_gyro_y;

    // Apply deadzone: if the gyro value is within the deadzone, don't update the platform
    if (filtered_gyro_y > -DEADZONE && filtered_gyro_y < DEADZONE) {
        filtered_gyro_y = 0;  // No movement if within the deadzone
    }

    // Update platform acceleration based on gyro input
    platform_acceleration = filtered_gyro_y / SCALE_FACTOR;  // Apply scaling factor

    // Update platform velocity based on the acceleration
    platform_velocity += platform_acceleration;

    // Apply friction if the platform is not being accelerated by the gyro
    if (platform_acceleration == 0) {
        if (platform_velocity > 0) {
            platform_velocity -= FRICTION;  // Apply friction (deceleration)
        } else if (platform_velocity < 0) {
            platform_velocity += FRICTION;
        }
    }

    // Apply velocity limits (max speed)
    if (platform_velocity > MAX_VELOCITY) {
        platform_velocity = MAX_VELOCITY;
    }
    if (platform_velocity < -MAX_VELOCITY) {
        platform_velocity = -MAX_VELOCITY;
    }

    // Update the platform's position based on its velocity
    *platform_x += platform_velocity;

    // Apply boundary check and bounce the platform if it hits the edge of the screen
    if (*platform_x < 10) {
        *platform_x = 10;  // Keep platform at the left edge
        platform_velocity = -platform_velocity * BOUNCE_DAMPING;  // Reverse and dampen velocity (bounce effect)
    }
    if (*platform_x > LCD_PIXEL_WIDTH - 65) {  // Assuming platform is 60px wide (6 * 10px per char)
        *platform_x = LCD_PIXEL_WIDTH - 65;  // Keep platform at the right edge
        platform_velocity = -platform_velocity * BOUNCE_DAMPING;  // Reverse and dampen velocity (bounce effect)
    }
}

void PrisonerEscapeAnimation(void) {
    static int x = 7;
    static uint32_t last_update_time = 0;

    uint32_t now = HAL_GetTick();

    if (now - last_update_time < 50) {
        return;  //  update every 50ms
    }
    last_update_time = now;

    if (x >= 80) {
        return;  // Finished animation
    }

    // Draw prisoner normally in black
    LCD_DisplayCharColored(x, 88, '|', LCD_COLOR_RED);

    // Erase previous prisoner by drawing '|' in white color
    LCD_DisplayCharColored(x - 2, 88, '|', LCD_COLOR_WHITE);

    x += 2;  // Move forward
}

