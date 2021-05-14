#include <stdint.h>
#include "game_functions.h"
#include "sync_thread.h"

#define CALL_LUA_FUNCTION_PTR 0x00704CD0
#define GET_PLAYER_GUID_FUNCTION_PTR 0x00468550

get_player_guid_ft game_get_player_guid = (get_player_guid_ft) GET_PLAYER_GUID_FUNCTION_PTR;

void game_call_lua(const char *lua_command) {
    __asm {
        pushad
        mov edx, myNewWndProc 
        mov ecx, lua_command
        mov esi, CALL_LUA_FUNCTION_PTR
        call esi
        popad
    }
}
