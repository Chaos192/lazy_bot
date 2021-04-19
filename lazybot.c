#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "game_functions.h"

static char user_input[256];

bool get_user_input() {
    printf("\n>>>");
    bool input_successful = fgets(user_input, sizeof(user_input), stdin);
    user_input[strcspn(user_input, "\n")] = 0;
    return input_successful;
}

bool execute_user_input() {
    if (!strcmp("login", user_input)) {
        printf("Player is logged in: %d\n", get_player_guid() > 0);
    } else if (!strcmp("exit", user_input)) {
        return false;
    }
    return true;
}

void start_bot() {
    AllocConsole();
    FILE* fDummy;
    freopen_s(&fDummy, "CONOUT$", "w", stdout);
    freopen_s(&fDummy, "CONOUT$", "w", stderr);
    freopen_s(&fDummy, "CONIN$", "r", stdin);

    while (get_user_input() && execute_user_input());
    exit(0);
}
