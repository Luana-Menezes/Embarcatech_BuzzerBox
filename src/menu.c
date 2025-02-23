#include <string.h>
#include "pico/stdlib.h"
#include "../inc/menu.h"
#include "../inc/display.h"
#include "../inc/joystick.h"
#include "../inc/buzzer.h"


MusicMenu musicMenu;

void menuInit() {
    strncpy(musicMenu.songs[0], "Super Mario", SONG_NAME_LENGTH);
    strncpy(musicMenu.songs[1], "Pirates Carib", SONG_NAME_LENGTH);
    strncpy(musicMenu.songs[2], "Shape of You", SONG_NAME_LENGTH);
    
    musicMenu.currentSelection = 0;
    musicMenu.songCount = MAX_SONGS;
}

void menuDisplay() {
    displayClear();
    ssd1306_draw_string(display, 20, 0, "SELECT SONG");
    
    for (int i = 0; i < musicMenu.songCount; i++) {
        if (i == musicMenu.currentSelection) {
            char selectedSong[SONG_NAME_LENGTH + 3];
            snprintf(selectedSong, sizeof(selectedSong), "> %s", musicMenu.songs[i]);
            ssd1306_draw_string(display, 0, (i * 16) + 16, selectedSong);
        } else {
            ssd1306_draw_string(display, 0, (i * 16) + 16, musicMenu.songs[i]);
        }
    }
    
    render_on_display(display, &frame_area);
}

void menuNavigation() {
    uint16_t y_val = joystGetAxis(JOYSTICK_X_PIN);

    if (y_val > 3000) {
        musicMenu.currentSelection--;
        if (musicMenu.currentSelection < 0) {
            musicMenu.currentSelection = musicMenu.songCount - 1;
        }
        buzzerPlaySound(BUZZER_PIN, 1000, 50);
        menuDisplay();

    } else if (y_val < 1000) {
        musicMenu.currentSelection++;
        if (musicMenu.currentSelection >= musicMenu.songCount) {
            musicMenu.currentSelection = 0;
        }
        buzzerPlaySound(BUZZER_PIN, 1200, 50);
        menuDisplay();
    }
}

void menuStartSelected() {
    for (int i = 0; i <= 5; i++) {
        displayLoading(i);
        sleep_ms(1000);
    }
}

void displayLoading(int progress) {
    displayClear();
    ssd1306_draw_string(display, 36, 16, "LOADING");

    int barWidth = (progress * 100) / 5;
    for (int i = 0; i < barWidth; i++) {
        ssd1306_draw_line(display, 14 + i, 32, 14 + i, 40, true);
    }
    render_on_display(display, &frame_area);
}