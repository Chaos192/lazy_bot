#include <windows.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

bool set_debug_privileges();
HANDLE get_proc_handle_by_window_name(const char* window_name);

int main() {
    if (!set_debug_privileges()) {
        return EXIT_FAILURE;
    }

    HANDLE process_handle = get_proc_handle_by_window_name("World of Warcraft");
    if (!process_handle) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
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
