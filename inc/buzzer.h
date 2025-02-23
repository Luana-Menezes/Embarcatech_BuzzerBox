#pragma once

#include <stdint.h>

#define BUZZER_PIN 21

void buzzerInit(uint pin);
void buzzerPlaySound(uint pin, uint32_t frequency, uint duration_ms);
void buzzerPlaySong(uint pin, const uint* notes, const uint* durations, uint note_count);

void introMelodyWrapper(void);
void marioMelodyWrapper(void);
void pirateMelodyWrapper(void);
void shapeMelodyWrapper(void);
