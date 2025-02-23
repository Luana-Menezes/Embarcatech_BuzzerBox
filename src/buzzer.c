#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"
#include "../inc/buzzer.h"
#include "../inc/myNotes.h"
#include "../inc/mySongs.h"

#define BUZZER_PIN 21

void buzzerInit(uint pin) {
    gpio_set_function(pin, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(pin);
    pwm_set_gpio_level(pin, 0);
    pwm_set_enabled(slice_num, true);
}

void buzzerPlaySound(uint pin, uint32_t frequency, uint duration_ms) {
    if (frequency == 0) {
        pwm_set_gpio_level(pin, 0);
        sleep_ms(duration_ms);
        sleep_ms(50);
        return;
    }

    uint slice_num = pwm_gpio_to_slice_num(pin);
    uint32_t clock_freq = clock_get_hz(clk_sys);

    uint clock_div = 1;
    uint32_t wrap = clock_freq / (frequency * clock_div);
    
    while (wrap > 65535 && clock_div < 256) {
        clock_div *= 2;
        wrap = clock_freq / (frequency * clock_div);
    }

    pwm_set_clkdiv(slice_num, clock_div);
    pwm_set_wrap(slice_num, wrap);
    pwm_set_gpio_level(pin, wrap / 2);
    sleep_ms(duration_ms);

    pwm_set_gpio_level(pin, 0);
    sleep_ms(50);
}

void buzzerPlaySong(uint pin, const uint* notes, const uint* durations, uint note_count) {
    for (uint i = 0; i < note_count; i++) {
        uint duration = 1000 / durations[i];
        buzzerPlaySound(pin, notes[i], duration);
    }
}

void introMelodyWrapper(){
    buzzerPlaySong(BUZZER_PIN, intro_melody, intro_durations, intro_melody_size);
}

void marioMelodyWrapper(){
    buzzerPlaySong(BUZZER_PIN, mario_melody, mario_durations, mario_melody_size);
}

void pirateMelodyWrapper(){
    buzzerPlaySong(BUZZER_PIN, pirates_melody, pirates_durations, pirates_melody_size);
}

void shapeMelodyWrapper(){
    buzzerPlaySong(BUZZER_PIN, shape_melody, shape_durations, shape_melody_size);
}