#include <windows.h>
#include <stdio.h>

void bot() {
    AllocConsole();
    FILE *file_dummy;
    freopen_s(&file_dummy, "CONOUT$", "w", stdout);

    while (TRUE) {
        printf("Injected.\n");
        Sleep(1000);
    }
}

BOOL WINAPI DllMain(HINSTANCE inst, DWORD Reason, LPVOID Reserved) {
    if (Reason == DLL_PROCESS_ATTACH) {
        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)bot, NULL, 0, NULL);
    }
    return TRUE;
}
