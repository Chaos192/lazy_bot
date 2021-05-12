#include <windows.h>
#include <stdio.h>

#include "object_manager.h"

#define MYMENU_EXIT         (WM_APP + 101)
#define MYMENU_MESSAGEBOX   (WM_APP + 102)

HINSTANCE inj_inst;
HWND prnt_hWnd;

void bot();

LRESULT CALLBACK DLLWindowProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    return DefWindowProc (hwnd, message, wParam, lParam);
}

DWORD WINAPI ThreadProc( LPVOID lpParam )
{
	MSG messages;
	RegisterDLLWindowClass("InjectedDLLWindowClass");
	prnt_hWnd = FindWindow("Window Injected Into ClassName", "Window Injected Into Caption");
	HWND hwnd = CreateWindowEx (0, "InjectedDLLWindowClass", lpParam, WS_EX_PALETTEWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 400, 300, prnt_hWnd, NULL, inj_inst, NULL );
	ShowWindow (hwnd, SW_SHOWNORMAL);
	while (GetMessage (&messages, NULL, 0, 0))
	{
		TranslateMessage(&messages);
        	DispatchMessage(&messages);
	}
	return 1;
}

BOOL RegisterDLLWindowClass(char szClassName[])
{
    WNDCLASSEX wc;
    wc.hInstance =  inj_inst;
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
    wc.hbrBackground = (HBRUSH) COLOR_BACKGROUND;
    if (!RegisterClassEx (&wc))
		return 0;
    return 1;
}

BOOL WINAPI DllMain(HINSTANCE inst, DWORD Reason, LPVOID Reserved) {
    if (Reason == DLL_PROCESS_ATTACH) {
        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)bot, NULL, 0, NULL);
        inj_inst = inst;
        CreateThread(NULL, 0, ThreadProc, (LPVOID)"Kenny Bot", 0, NULL);
    }
    return TRUE;
}


void bot() {
    AllocConsole();
    FILE *file_dummy;
    freopen_s(&file_dummy, "CONOUT$", "w", stdout);
    printf("Injected.\n");


    while (TRUE) {
        if (GetAsyncKeyState(VK_END)) {
            system("cls");
            enumerate_visible_objects();
        }
        Sleep(100);
    }
}
