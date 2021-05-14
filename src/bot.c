#include <windows.h>
#include <stdbool.h>

#include "object_manager.h"

extern object_t local_player;
extern object_t units[100];

bool running = false;

void start() {
    if (!running) {
        printf("Starting Bot...\n");
        running = true;
    } else {
        printf("Bot already running.\n");
    }
}

void stop() {
    if (running) {
        printf("Stoping Bot...\n");
        running = false;
    } else {
        printf("Bot is already stopped.\n");
    }
}

void bot() {
    while (true) {
        if (running) {
            update();
            //go_to(local_player, units[0].position);
        }
        Sleep(500);
    }
}
