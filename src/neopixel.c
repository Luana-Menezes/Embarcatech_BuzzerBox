#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "ws2818b.pio.h"
#include "../inc/neopixel.h"



const RGBColor colors[5] = {
    {255, 0, 0},    // vermelho
    {255, 165, 0},  // laranja
    {255, 255, 0},  // amarelo
    {0, 255, 0},    // verde
    {0, 0, 255}     // azul
};

npLED_t leds[LED_COUNT];
PIO np_pio;
uint sm;

void npInit(uint pin) {
    uint offset = pio_add_program(pio0, &ws2818b_program);
    np_pio = pio0;

    sm = pio_claim_unused_sm(np_pio, false);
    if (sm < 0) {
      np_pio = pio1;
      sm = pio_claim_unused_sm(np_pio, true);
    }
  
    ws2818b_program_init(np_pio, sm, offset, pin, 800000.f);
  
    for (uint i = 0; i < LED_COUNT; ++i) {
      leds[i].R = 0;
      leds[i].G = 0;
      leds[i].B = 0;
    }

    npWrite();
}

void npSetLED(const uint index, const uint8_t r, const uint8_t g, const uint8_t b, uint8_t brightness) {
    if (index >= LED_COUNT) return;

    if (brightness > 100) brightness = 100;

    uint8_t adj_r = (r * brightness) / 100;
    uint8_t adj_g = (g * brightness) / 100;
    uint8_t adj_b = (b * brightness) / 100;

    leds[index].R = adj_r;
    leds[index].G = adj_g;
    leds[index].B = adj_b;
}

void npClear() {
    for (uint i = 0; i < LED_COUNT; ++i)
      npSetLED(i, 0, 0, 0, 0);
}

void npWrite() {
    for (uint i = 0; i < LED_COUNT; ++i) {
      pio_sm_put_blocking(np_pio, sm, leds[i].G);
      pio_sm_put_blocking(np_pio, sm, leds[i].R);
      pio_sm_put_blocking(np_pio, sm, leds[i].B);
    }
    sleep_us(100);
}

int getLinearIndex(int x, int y) {
    int row = y;
    int i;
    
    if (row % 2 == 0) {
        i = row * 5 + (4 - x);
    } else {
        i = row * 5 + x;
    }
    
    return i;
}

void musicEqualizer(uint8_t brightness) {
    static int heights[5] = {0, 0, 0, 0, 0};
    static int target_heights[5] = {0, 0, 0, 0, 0};
    
    for(int i = 0; i < 5; i++) {
        if(rand() % 3 == 0) {
            target_heights[i] = rand() % 6;
        }
        
        if(heights[i] < target_heights[i]) heights[i]++;
        if(heights[i] > target_heights[i]) heights[i]--;
    }
    
    npClear();
    
    for(int x = 0; x < 5; x++) {
        for(int y = 0; y < heights[x]; y++) {
            int i = getLinearIndex(x, y);
            npSetLED(i, colors[x].R, colors[x].G, colors[x].B, brightness);
        }
    }
    npWrite();
}

void npMusicAnimation(uint32_t duration) {
    absolute_time_t end_time = make_timeout_time_ms(duration);
    
    while (!time_reached(end_time)) {
        musicEqualizer(10);
        sleep_ms(50);
    }
    
    npClear();
    npWrite();
}