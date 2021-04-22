#include <windows.h>
#include <stdbool.h>

#include "lazybot.h"

BOOL WINAPI DllMain(HINSTANCE hinstDLL,
                    DWORD Reason,
                    LPVOID Reserved) {
    if (Reason == DLL_PROCESS_ATTACH) {
        CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)bot, NULL, NULL, NULL);
    }
    return true;
}
