#include <windows.h>
#include <stdio.h>

#include "gui.h"
#include "bot.h"

void run() {
    AllocConsole();
    FILE *file_dummy;
    freopen_s(&file_dummy, "CONOUT$", "w", stdout);
    printf("Injected.\n");

    // open gui
    CreateThread(NULL, 0, ThreadProc, (LPVOID)"Kenny Bot", 0, NULL);

    initialize_bot();
}

BOOL WINAPI DllMain(HINSTANCE inst, DWORD Reason, LPVOID Reserved) {
    if (Reason == DLL_PROCESS_ATTACH) {
        inj_inst = inst;
        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)run, NULL, 0, NULL);
    }
    return TRUE;
}

