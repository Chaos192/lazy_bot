#include <windows.h>
#include <stdio.h>

#include "object_manager.h"

void bot();

BOOL WINAPI DllMain(HINSTANCE inst, DWORD Reason, LPVOID Reserved) {
    if (Reason == DLL_PROCESS_ATTACH) {
        HWND dummyHWND = CreateWindowA("STATIC","dummy",WS_VISIBLE,0,0,100,100,NULL,NULL,NULL,NULL);
        SetWindowTextA(dummyHWND,"Dummy Window!");
        ShowWindow(dummyHWND, 1);
        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)bot, NULL, 0, NULL);
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
