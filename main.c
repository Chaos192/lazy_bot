#include <windows.h>
#include <stdbool.h>
#include <stdio.h>

#include "lazybot.h"

BOOL WINAPI DllMain(
    HINSTANCE hinstDLL, 
    DWORD Reason,
    LPVOID lpReserved)
{
    if (Reason == DLL_PROCESS_ATTACH) {
        CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)start_bot, NULL, NULL, NULL);
    }
    return TRUE;
}
