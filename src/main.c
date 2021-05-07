#include <windows.h>
#include <stdio.h>

#include "object_manager.h"

void bot();

BOOL WINAPI DllMain(HINSTANCE inst, DWORD Reason, LPVOID Reserved) {
    if (Reason == DLL_PROCESS_ATTACH) {
        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)bot, NULL, 0, NULL);
    }
    return TRUE;
}

void bot() {
    AllocConsole();
    FILE *file_dummy;
    freopen_s(&file_dummy, "CONOUT$", "w", stdout);

    while (TRUE) {
        if (GetAsyncKeyState('M')) {
            enumerate_visible_objects();
        }
        if (GetAsyncKeyState('Q')) {
            exit(0);
        }
        Sleep(100);
    }
}
