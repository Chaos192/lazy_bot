#include <windows.h>
#include <stdint.h>

#include "game_functions.h"
#include "utils.h"
#include "sync_thread.h"

#define WINDOW_NAME "Lazy Bot"

#define JUMP 0

LRESULT CALLBACK DLLWindowProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
        case WM_CREATE:
            CreateWindowW(L"Button", L"Jump",
                          WS_CHILD | WS_VISIBLE | WS_BORDER,
                          5, 10, 70, 20, hwnd, (HMENU)JUMP, NULL, NULL);
            break;
        case WM_COMMAND:
            switch (wParam) {
                case JUMP:
                    //game_call_lua("Jump()", "");
                    sync();
                    break;
            }
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default: 
			return DefWindowProc (hwnd, message, wParam, lParam);
    }
    return 0;
}

BOOL RegisterDLLWindowClass(const char *szClassName, HINSTANCE instance_handle) {
    WNDCLASSEX wc;
    wc.hInstance = instance_handle;
    wc.lpszClassName = (LPCSTR)szClassName;
    wc.lpfnWndProc = DLLWindowProc;
    wc.style = CS_DBLCLKS;
    wc.cbSize = sizeof (WNDCLASSEX);
    wc.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wc.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor (NULL, IDC_ARROW);
    wc.lpszMenuName = NULL;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hbrBackground = (HBRUSH) 0x0;
    if (!RegisterClassEx (&wc))
		return 0;
    return 1;
}

uint32_t WINAPI start_gui(LPVOID injected_instance) {
    setup_client(); // do things like enable lua and correct click to move
    MSG messages;
    RegisterDLLWindowClass("InjectedDLLWindowClass", *(HINSTANCE*)injected_instance);
    HWND prnt_hWnd = FindWindow("Window Injected Into ClassName", 
                           "Window Injected Into Caption");
    HWND hWnd = CreateWindowEx(0, 
                               "InjectedDLLWindowClass", 
                               WINDOW_NAME,
                               WS_SYSMENU | WS_VISIBLE,
                               CW_USEDEFAULT, CW_USEDEFAULT,
                               500, 250,
                               prnt_hWnd,
                               NULL,
                               *(HINSTANCE*)injected_instance,
                               NULL);
    ShowWindow(hWnd, SW_SHOWNORMAL);
    while (GetMessage(&messages, NULL, 0, 0)) {
        TranslateMessage(&messages);
        DispatchMessage(&messages);
    }
    return 1;
}

