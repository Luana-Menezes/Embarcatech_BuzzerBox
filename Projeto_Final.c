#include <stdio.h>
#include "pico/stdlib.h"
#include "inc/systemlogic.h"
#include "inc/neopixel.h"
#include "inc/display.h"
#include "inc/buzzer.h"
#include "inc/joystick.h"
#include "inc/menu.h"
#include "inc/myBitmaps.h"
#include "inc/myNotes.h"
#include "inc/mySongs.h"

void cleanupCore1() {
    multicore_reset_core1();
    sleep_ms(100);
}

int main()
{
    stdio_init_all();

    npInit(LED_PIN);
    displayInit();
    displayBitmapMode();
    buzzerInit(BUZZER_PIN);
    joystInit();
    menuInit();

    while (true) {
        switch (systemState) {
            case STATE_INTRO:
                if (systemStateChanged) {
                    multicore_launch_core1(introMelodyWrapper);
                    ssd1306_draw_bitmap(&display_bm, &bitmap_intro);
                    sleep_ms(5000);
                    cleanupCore1();

                    displayStringMode();

                    systemStateChanged = false;
                    systemState = STATE_MENU;
                    systemStateChanged = true;
                }
                break;
            case STATE_MENU:
                if (systemStateChanged) {
                    menuDisplay();
                    systemStateChanged = false;
                }
                menuNavigation();
                break;
            case STATE_LOADING:
                if (systemStateChanged) {
                    menuStartSelected();

                    systemStateChanged = false;
                    systemState = STATE_PLAYING;
                    systemStateChanged = true;
                }
                break;
            case STATE_PLAYING:
                if (systemStateChanged) {
                    displayClear();
                    cleanupCore1();
                    switch (musicMenu.currentSelection){
                        case 0:
                            multicore_launch_core1(marioMelodyWrapper);                            
                            npMusicAnimation(80000);
                            cleanupCore1();
                            break;
                        case 1:
                            multicore_launch_core1(pirateMelodyWrapper);
                            npMusicAnimation(45000);
                            cleanupCore1();
                            break;
                        case 2:
                            multicore_launch_core1(shapeMelodyWrapper);
                            npMusicAnimation(90000);
                            cleanupCore1();
                            break;
                    }

                    systemStateChanged = false;
                    systemState = STATE_MENU;
                    systemStateChanged = true;

                }

                break;
        }

        sleep_ms(50);
    }

    return 0;
}
