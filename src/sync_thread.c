#include <windows.h>

WNDPROC prevWndProc;
HWND wow_window;

LRESULT CALLBACK myNewWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if (uMsg == WM_USER) {
        // TODO: Understand why the fuck calling from the main thread
        // generate different opcodes.. omg, I'm so dump t-t
        //game_call_lua("Jump()", "");
        static char* jump_string = "Jump()";
        __asm {
            pushad
            mov edx, myNewWndProc 
            mov ecx, jump_string
            mov esi, 0x00704CD0
            call esi
            popad
        }
    }
    return CallWindowProc(prevWndProc, hwnd, uMsg, wParam, lParam);
}

void sync() {
    wow_window = FindWindow(NULL, "World of Warcraft");
    prevWndProc = (WNDPROC) SetWindowLong(wow_window, GWL_WNDPROC, (LONG_PTR)&myNewWndProc);
}

void invoke() {
    SendMessage(wow_window, WM_USER, 0, 0);
}
