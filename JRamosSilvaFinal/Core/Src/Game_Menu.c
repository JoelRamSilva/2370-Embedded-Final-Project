#include "Game_Menu.h"
#include "LCD_Driver.h"

// Play Button Dimensions
#define START_BUTTON_X 50
#define START_BUTTON_Y 144
#define START_BUTTON_WIDTH 140
#define START_BUTTON_HEIGHT 50

// Play Button Dimensions
#define OPTIONS_BUTTON_X 50
#define OPTIONS_BUTTON_Y 210
#define OPTIONS_BUTTON_WIDTH 140
#define OPTIONS_BUTTON_HEIGHT 50

// Initialize the Menu
void menu_init(void) {
    menu_render();
}

// Render the Start Menu
void menu_render(void) {
    // Clear screen
    LCD_Clear(0, LCD_COLOR_BLACK);

    // Draw Title
	LCD_SetTextColor(LCD_COLOR_RED);
	LCD_SetFont(&Font16x24);

	LCD_DisplayChar(83,50,'S');
	LCD_DisplayChar(99,50,'P');
	LCD_DisplayChar(115,50,'A');
	LCD_DisplayChar(131,50,'C');
	LCD_DisplayChar(147,50,'E');

	LCD_DisplayChar(55,80,'I');
	LCD_DisplayChar(67,80,'N');
	LCD_DisplayChar(83,80,'V');
	LCD_DisplayChar(99,80,'A');
	LCD_DisplayChar(116,80,'D');
	LCD_DisplayChar(131,80,'E');
	LCD_DisplayChar(147,80,'R');
	LCD_DisplayChar(163,80,'S');

    // Draw Start Button
    for (int y = START_BUTTON_Y; y < START_BUTTON_Y + START_BUTTON_HEIGHT; y++) {
        for (int x = START_BUTTON_X; x < START_BUTTON_X + START_BUTTON_WIDTH; x++) {
            LCD_Draw_Pixel(x, y, LCD_COLOR_GREEN);
        }
    }

	LCD_SetTextColor(LCD_COLOR_BLACK);
	LCD_SetFont(&Font16x24);
	LCD_DisplayChar(88,158,'P');
	LCD_DisplayChar(104,158,'L');
	LCD_DisplayChar(120,158,'A');
	LCD_DisplayChar(136,158,'Y');

    // Draw Options Button
    for (int y = OPTIONS_BUTTON_Y; y < OPTIONS_BUTTON_Y + OPTIONS_BUTTON_HEIGHT; y++) {
        for (int x = OPTIONS_BUTTON_X; x < OPTIONS_BUTTON_X + OPTIONS_BUTTON_WIDTH; x++) {
            LCD_Draw_Pixel(x, y, LCD_COLOR_GREEN);
        }
    }

	LCD_SetTextColor(LCD_COLOR_BLACK);
	LCD_SetFont(&Font16x24);
	LCD_DisplayChar(70,224,'O');
	LCD_DisplayChar(87,224,'P');
	LCD_DisplayChar(102,224,'T');
	LCD_DisplayChar(114,224,'I');
	LCD_DisplayChar(126,224,'O');
	LCD_DisplayChar(143,224,'N');
	LCD_DisplayChar(158,224,'S');

}

// Handle Touch Events
void menu_handle_touch(uint16_t x, uint16_t y) {

    // Check if "Start" button was touched
    if (x > START_BUTTON_X && x < (START_BUTTON_X + START_BUTTON_WIDTH) &&
        y > START_BUTTON_Y && y < (START_BUTTON_Y + START_BUTTON_HEIGHT)) {

        // "Start" button pressed
        LCD_Clear(0, LCD_COLOR_BLACK);
        HAL_Delay(1000);

        // Call game start function
        extern void startGame(void);
        startGame();
    }
}
