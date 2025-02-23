#pragma once

#define LED_COUNT 25
#define LED_PIN 7

typedef struct pixel_t {
    uint8_t G, R, B;
} npLED_t;

typedef struct {
    uint8_t G;
    uint8_t R;
    uint8_t B;
} RGBColor;


void npInit(uint pin);
void npSetLED(const uint index, const uint8_t r, const uint8_t g, const uint8_t b, uint8_t brightness);
void npClear(void);
void npWrite(void);
void npMusicAnimation(uint32_t duration);