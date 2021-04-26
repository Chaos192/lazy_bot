#include <windows.h>

#include "utils.h"

void write_bytes(DWORD addr, char bytes[]) {
    HANDLE proc_handle = get_wow_handle(); 

    WriteProcessMemory(proc_handle, (void*)addr, bytes, strlen(bytes), NULL);

    CloseHandle(proc_handle);
}
