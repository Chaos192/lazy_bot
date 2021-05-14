#include <windows.h>
//#include "game_functions.h"

WNDPROC prevWndProc;
HWND wow_window;

char *lua_function_to_exec;

LRESULT CALLBACK myNewWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if (uMsg == WM_USER) {
        // TODO: Understand why the fuck calling from the main thread
        // generate different opcodes.. omg, I'm so dump t-t
        //game_call_lua("Jump()", "");
        game_call_lua(lua_function_to_exec);
    }
    return CallWindowProc(prevWndProc, hwnd, uMsg, wParam, lParam);
}

void sync() {
    wow_window = FindWindow(NULL, "World of Warcraft");
    prevWndProc = (WNDPROC) SetWindowLong(wow_window, GWL_WNDPROC, (LONG_PTR)&myNewWndProc);
}

void invoke(char *lua_function) {
    lua_function_to_exec = lua_function;
    SendMessage(wow_window, WM_USER, 0, 0);
}
