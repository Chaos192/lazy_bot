#include <windows.h>
#include <stdio.h>
#include <stdbool.h>

#include "game.h"
#include "object_manager.h"

void bot() {
    AllocConsole();
    FILE *fDummy;
    freopen_s(&fDummy, "CONOUT$", "w", stdout);

    printf("Injected...\n");

    while (true) {
        if(GetAsyncKeyState('E')) {
            system("cls");
            if (get_player_guid() > 0) {
                enumerate_visible_objects();
            }
        }
        Sleep(100);
    }
}
