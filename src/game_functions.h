#define CALL_LUA_FUNCTION_PTR 0x00704CD0

typedef void (__fastcall* call_lua_ft)(char *statement, char* garbage);

call_lua_ft game_call_lua = (call_lua_ft) CALL_LUA_FUNCTION_PTR;
