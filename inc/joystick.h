#pragma once

#include <stdint.h>
#include <stdbool.h>

#define JOYSTICK_X_PIN 26
#define JOYSTICK_Y_PIN 27
#define JOYSTICK_BTN_PIN 22

void joystInit(void);
uint16_t joystGetAxis(uint pin);
void joystBtnCallback(uint gpio, uint32_t events);