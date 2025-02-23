#pragma once

#include <stdint.h>
#include "inc/ssd1306.h"

#define DISPLAY_I2C_PORT i2c1
#define DISPLAY_I2C_SDA 14
#define DISPLAY_I2C_SCL 15

extern uint8_t display[];
extern struct render_area frame_area;
extern ssd1306_t display_bm;

void displayInit(void);
void displayString(const char* text[], int lines);
void displayClear(void);
void displayBitmapMode(void);
void displayStringMode(void);