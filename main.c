#include <windows.h>
#include <stdbool.h>
#include <stdio.h>

#define GET_PLAYER_GUID_FUN_PTR 0x00468550

typedef int (__cdecl* login_state)();

void start_bot() {
    AllocConsole();
    FILE* fDummy;
    freopen_s(&fDummy, "CONOUT$", "w", stdout);

    login_state get_player_login_state = (login_state)GET_PLAYER_GUID_FUN_PTR;
    while (true) {
        if ((GetAsyncKeyState('M')) & 0x8000) {
            printf("Player is logged in: %d\n", get_player_login_state() > 0);
        }
        Sleep(100);
    }
}

BOOL WINAPI DllMain(
    HINSTANCE hinstDLL,  // handle to DLL module
    DWORD fdwReason,     // reason for calling function
    LPVOID lpReserved)  // reserved
{
    // Perform actions based on the reason for calling.
    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)start_bot, NULL, NULL, NULL);
        break;

    case DLL_THREAD_ATTACH:
        // Do thread-specific initialization.
        break;

    case DLL_THREAD_DETACH:
        // Do thread-specific cleanup.
        break;

    case DLL_PROCESS_DETACH:
        // Perform any necessary cleanup.
        break;
    }
    return TRUE;  // Successful DLL_PROCESS_ATTACH.
}