#include <windows.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "game.h"
#include "objects.h"

void bot() {
    AllocConsole();
    FILE *fDummy;
    freopen_s(&fDummy, "CONOUT$", "w", stdout);

    printf("Injected...\n");

    while (true) {
        if (get_player_guid() > 0) {
            system("cls");
            enumerate_visible_objects();
        }
        if(GetAsyncKeyState('R')) {
        } else if (GetAsyncKeyState(VK_END)) {
            exit(0);
        }
        Sleep(1000);
    }
}
