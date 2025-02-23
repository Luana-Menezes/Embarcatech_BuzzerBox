#pragma once

#include <stdbool.h>

typedef enum {
    STATE_INTRO,
    STATE_MENU,
    STATE_LOADING,
    STATE_PLAYING
} SystemState;

extern SystemState systemState;
extern bool systemStateChanged;