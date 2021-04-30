#include <windows.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "game.h"
#include "objects.h"
#include "utils.h"

void bot() {
    AllocConsole();
    FILE *fDummy;
    freopen_s(&fDummy, "CONOUT$", "w", stdout);

	fix_click_to_move();
    while (true) {
        if (get_player_guid() > 0) {
            system("cls");
            enumerate_visible_objects();
        } else if (GetAsyncKeyState("I")) {
            game_click_to_move(player_ptr, Move, NULL, closest_unit_xyz, 0);
        } else if (GetAsyncKeyState(VK_END)) {
            exit(0);
        }
        Sleep(100);
    }
}
