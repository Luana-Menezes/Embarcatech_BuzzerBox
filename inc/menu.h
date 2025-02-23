#pragma once

#define MAX_SONGS 3
#define SONG_NAME_LENGTH 16

typedef struct {
    char songs[MAX_SONGS][SONG_NAME_LENGTH];
    int currentSelection;
    int songCount;
} MusicMenu;

extern MusicMenu musicMenu;

void menuInit(void);
void menuDisplay(void);
void menuNavigation(void);
void menuStartSelected(void);
void displayLoading(int progress);
int getCurrentSelection(void);