#include <windows.h>
#include <stdbool.h>
#include <stdint.h>

#include "gui.h"

HINSTANCE instance_handle;

bool WINAPI DllMain(HINSTANCE instance_handle_dll, DWORD reason, LPVOID reserved) {
    instance_handle = instance_handle_dll;
    switch (reason) {
        case DLL_PROCESS_ATTACH:
            CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)start_gui, &instance_handle, 0, NULL);
            break;
    }
    return true;
}
