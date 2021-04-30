#include "objects.h"
#include <stdbool.h>
#include <windows.h>

typedef int(__cdecl *game_get_player_guid)();
typedef bool(__thiscall *game_click_to_move)(DWORD, click_to_move_t, DWORD, position_t *, float);

static const game_get_player_guid get_player_guid = 
    (game_get_player_guid)0x00468550;
static const game_click_to_move click_to_move = (game_click_to_move)0x00611130;
