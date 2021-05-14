#define CALL_LUA_FUNCTION_PTR 0x00704CD0
#define GET_PLAYER_GUID_FUNCTION_PTR 0x00468550

typedef void (__fastcall* call_lua_ft)(char *statement, char* garbage);
typedef uint64_t (__cdecl* get_player_guid_ft)();

call_lua_ft game_call_lua = (call_lua_ft) CALL_LUA_FUNCTION_PTR;
get_player_guid_ft game_get_player_guid = (get_player_guid_ft) GET_PLAYER_GUID_FUNCTION_PTR;
