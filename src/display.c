#include <string.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "../inc/display.h"

struct render_area frame_area = {
    start_column : 0,
    end_column : ssd1306_width - 1,
    start_page : 0,
    end_page : ssd1306_n_pages - 1
};

uint8_t display[ssd1306_buffer_length];
ssd1306_t display_bm;

void displayInit(){
    i2c_init(DISPLAY_I2C_PORT, ssd1306_i2c_clock * 1000);
  
    gpio_set_function(DISPLAY_I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(DISPLAY_I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(DISPLAY_I2C_SDA);
    gpio_pull_up(DISPLAY_I2C_SCL);

    ssd1306_init();
    calculate_render_area_buffer_length(&frame_area);
    displayClear();
}

void displayClear() {
    memset(display, 0, ssd1306_buffer_length);
    render_on_display(display, &frame_area);
}

void displayBitmapMode(){
    displayClear();

    ssd1306_init_bm(&display_bm, ssd1306_width, ssd1306_height, false, ssd1306_i2c_address, DISPLAY_I2C_PORT);
    ssd1306_config(&display_bm);
}

void displayStringMode(){
    ssd1306_init();
    displayClear();
}

void displayString(const char *text[], int lines) {
    int y = 0;
    for (uint i = 0; i < count_of(text); i++)
    {
        ssd1306_draw_string(display, 5, y, text[i]);
        y += 8;
    }
    render_on_display(display, &frame_area);
}

  