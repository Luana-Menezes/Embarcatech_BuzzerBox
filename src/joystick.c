
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "../inc/joystick.h"
#include "../inc/systemlogic.h"

uint16_t joystGetAxis(uint pin) {
    adc_select_input(pin - 26);
    return adc_read();
}

void joystInit() {
    adc_init();
    adc_gpio_init(JOYSTICK_X_PIN);
    adc_gpio_init(JOYSTICK_Y_PIN);
    
    gpio_init(JOYSTICK_BTN_PIN);
    gpio_set_dir(JOYSTICK_BTN_PIN, GPIO_IN);
    gpio_pull_up(JOYSTICK_BTN_PIN);
    gpio_set_irq_enabled_with_callback(JOYSTICK_BTN_PIN, GPIO_IRQ_EDGE_FALL, true, &joystBtnCallback);
}

void joystBtnCallback(uint gpio, uint32_t events){
    if (gpio == JOYSTICK_BTN_PIN && systemState == STATE_MENU) {
        systemState = STATE_LOADING;
        systemStateChanged = true;
    }
}