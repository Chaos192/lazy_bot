#include <windows.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#define DLL_NAME "kenny_bot.dll"
#define PROCESS_WINDOW_NAME "World of Warcraft"

bool set_debug_privileges();
HANDLE get_proc_handle_by_window_name(const char* window_name);
bool inject_dll(HANDLE proc_handle, const char* dll_name);

int main() {
    if (!set_debug_privileges()) {
        return EXIT_FAILURE;
    }

    HANDLE process_handle = get_proc_handle_by_window_name(PROCESS_WINDOW_NAME);
    if (!process_handle) {
        return EXIT_FAILURE;
    }

    if (!inject_dll(process_handle, DLL_NAME)) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

bool inject_dll(HANDLE proc_handle, const char *dll_name) {
    puts("[*] Injecting DLL.");
    char dll_path[512];
    DWORD status = GetFullPathName(dll_name, sizeof(dll_path), dll_path, NULL);

    HANDLE dll_handle = CreateFileA(dll_path, 
                                    GENERIC_READ, 
                                    0, 
                                    NULL, 
                                    OPEN_EXISTING,
                                    FILE_ATTRIBUTE_NORMAL,
                                    NULL);

    uint32_t dll_size = GetFileSize(dll_handle, NULL);

    // Allocating space for the dll in the remote process
    void *allocated_space = VirtualAllocEx(proc_handle, 
                                           NULL, 
                                           dll_size, 
                                           MEM_COMMIT|MEM_RESERVE,
                                           PAGE_EXECUTE_READWRITE);
    if (!allocated_space) {
        puts("[!] Could not allocate space for dll in remtoe process.");
        return false;
    }

    // Load the dll in our heap and then write to the remote process
    void *buffer = HeapAlloc(GetProcessHeap(), 0, dll_size);
    if (!buffer) {
        puts("[!] Could not allocate space for the dll in our heap.\n");
        return false;
    }
    ReadFile(dll_handle, buffer, dll_size, NULL, NULL);
    WriteProcessMemory(proc_handle, allocated_space, buffer, dll_size, NULL);

    // TODO: Figure out how to execute the dll...

    return true;
}

HANDLE get_proc_handle_by_window_name(const char* window_name) {
    puts("[*] Waiting for window ...");
    HWND window_handle;
    while (!(window_handle = FindWindow(NULL, window_name)));

    uint32_t proc_id;
    GetWindowThreadProcessId(window_handle, &proc_id);
    if (!proc_id) {
        puts("[!] Could not get process id.");
        return NULL;
    }

    HANDLE proc_handle = OpenProcess(PROCESS_CREATE_THREAD |
                                     PROCESS_QUERY_INFORMATION |
                                     PROCESS_VM_OPERATION |
                                     PROCESS_VM_WRITE |
                                     PROCESS_VM_READ,
                                     false,
                                     proc_id);
    if (!proc_handle) {
        puts("[!] Could not get process handle. Check debug privileges.");
    }
    return proc_handle;
}

bool set_debug_privileges() {
    puts("[*] Setting debug privileges.");
    TOKEN_PRIVILEGES tp;
    LUID luid;

    HANDLE token_handle;
    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &token_handle)) {
        puts("[!] Could not get process token.");
        return false;
    }

    if (!LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &luid)) {
        puts("[!] Could not look up privilege value for SE_DEBUG_NAME.");
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
        puts("[!] Could not adjust token privileges.");
        return false;
    }

    return true;
}
