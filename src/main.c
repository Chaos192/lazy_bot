#include <windows.h>
#include <stdbool.h>

#include "lazybot.h"

BOOL WINAPI DllMain(HINSTANCE hinstDLL,
                    DWORD Reason,
                    LPVOID Reserved) {
    if (Reason == DLL_PROCESS_ATTACH) {
        CreateThread(0, 0, (LPTHREAD_START_ROUTINE)bot, NULL, 0, NULL);
    }
    return true;
}
