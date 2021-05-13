#include <windows.h>

WNDPROC prevWndProc;

void jump() {
}

LRESULT CALLBACK myNewWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if (GetAsyncKeyState(VK_END)) {
        game_call_lua("Jump()", "");
    }
    return CallWindowProc(prevWndProc, hwnd, uMsg, wParam, lParam);
}

void sync() {
    HWND wow_window = FindWindow(NULL, "World of Warcraft");
    prevWndProc = (WNDPROC) SetWindowLong(wow_window, GWL_WNDPROC, (LONG_PTR)&myNewWndProc);
    SendMessage(wow_window, WM_USER, 0, 0);
}
