#include <windows.h>
#include <stdbool.h>

bool running = false;

void start() {
    if (!running) {
        printf("Starting Bot...\n");
        running = false;
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
    while (running) {
        printf("Top State");
        Sleep(700);
    }
}
