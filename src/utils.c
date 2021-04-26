#include <windows.h>
#include <stdio.h>
#include <stdbool.h>

HANDLE get_wow_handle() {
    printf("Waiting for window...\n");
    HWND window_handle = NULL;
    while (!(window_handle = FindWindow(NULL, "World of Warcraft"))) Sleep(100);

    DWORD proc_id;
    GetWindowThreadProcessId(window_handle, &proc_id);
    if (!proc_id) {
        printf("Could not get process id.\n");
        exit(1);
    }

    HANDLE proc_handle = OpenProcess(PROCESS_CREATE_THREAD | 
                                     PROCESS_QUERY_INFORMATION | 
                                     PROCESS_VM_OPERATION | 
                                     PROCESS_VM_WRITE | 
                                     PROCESS_VM_READ, false, proc_id);
    if (!proc_handle) {
        printf("Could not get process handle. Check debug privileges.\n");
        exit(1);
    }

    return proc_handle;
}
