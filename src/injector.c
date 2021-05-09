#include <windows.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define DLL_PATH "C:\\kenny\\bin\\kenny_bot.dll"
#define GAME_PATH "C:\\Program Files (x86)\\World of Warcraft\\WoW.exe"
#define PROCESS_WINDOW_NAME "World of Warcraft"

HANDLE get_proc_handle_by_window_name(const char* window_name);
bool inject_dll(HANDLE proc_handle);
bool set_debug_privileges();
void setup_windows_layout();

int main() {
    ShellExecuteA(NULL, "open", GAME_PATH, NULL, NULL, SW_SHOWDEFAULT);

    if (!set_debug_privileges()) {
        return EXIT_FAILURE;
    }

    HANDLE process_handle = get_proc_handle_by_window_name(PROCESS_WINDOW_NAME);
    if (!process_handle) {
        return EXIT_FAILURE;
    }

    if (!inject_dll(process_handle)) {
        return EXIT_FAILURE;
    }

    setup_windows_layout();
    CloseHandle(process_handle);
    return EXIT_SUCCESS;
}

void setup_windows_layout() {
    Sleep(1000);
    HWND wow_window = FindWindow(NULL, "World of Warcraft");
    HWND console_window = FindWindow(NULL, GAME_PATH);

    MoveWindow(wow_window, -15, 0, 800, 600, FALSE);
    MoveWindow(console_window, 770, 0, 1366-760, 750, TRUE);

    SetForegroundWindow(wow_window);
}

bool inject_dll(HANDLE proc_handle) {
    printf("[*] Injecting DLL.\n");
    size_t dll_path_length = strlen(DLL_PATH) + 1;

    void *allocated_space = VirtualAllocEx(proc_handle, 
                                           NULL, 
                                           dll_path_length, 
                                           MEM_COMMIT|MEM_RESERVE, 
                                           PAGE_EXECUTE_READWRITE);

    WriteProcessMemory(proc_handle, allocated_space, DLL_PATH, dll_path_length, NULL);

    void *load_lib_addr = 
        GetProcAddress(GetModuleHandle(TEXT("kernel32.dll")), "LoadLibraryA");

    CreateRemoteThread(proc_handle, 
                       NULL, 
                       0, 
                       (LPTHREAD_START_ROUTINE)load_lib_addr, 
                       allocated_space, 
                       0, 
                       NULL);

    VirtualFreeEx(proc_handle, allocated_space, dll_path_length, MEM_DECOMMIT|MEM_RELEASE);

    return true;
}

HANDLE get_proc_handle_by_window_name(const char* window_name) {
    printf("[*] Waiting for window ...\n");
    HWND window_handle;
    while (!(window_handle = FindWindow(NULL, window_name)));

    uint32_t proc_id;
    GetWindowThreadProcessId(window_handle, &proc_id);

    HANDLE proc_handle = OpenProcess(PROCESS_CREATE_THREAD |
                                     PROCESS_QUERY_INFORMATION |
                                     PROCESS_VM_OPERATION |
                                     PROCESS_VM_WRITE |
                                     PROCESS_VM_READ,
                                     false,
                                     proc_id);
    if (!proc_handle) {
        printf("[!] Could not get process handle. Check debug privileges.\n");
    }
    return proc_handle;
}

bool set_debug_privileges() {
    printf("[*] Setting debug privileges.\n");
    TOKEN_PRIVILEGES tp;
    LUID luid;

    HANDLE token_handle;
    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &token_handle)) {
        printf("[!] Could not get process token.\n");
        return false;
    }

    if (!LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &luid)) {
        printf("[!] Could not look up privilege value for SE_DEBUG_NAME.\n");
        return false;
    }

    tp.PrivilegeCount = 1;
    tp.Privileges[0].Luid = luid;
    tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

    if (!AdjustTokenPrivileges(token_handle, 
                               false, 
                               &tp, 
                               0,
                               (PTOKEN_PRIVILEGES) NULL,
                               (PDWORD) NULL)) 
    {
        printf("[!] Could not adjust token privileges.\n");
        return false;
    }

    return true;
}
