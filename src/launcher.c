#include <windows.h>
#include <stdio.h>
#include <stdbool.h>

#define GAME_PATH "\"C:\\Program Files (x86)\\World of Warcraft\\WoW.exe\""
#define DLL_PATH "C:\\Users\\user\\kenny_bot\\bin\\kenny_bot.dll"

void setup_windows_layout() {
    HWND wow_window_handle = FindWindow(NULL, "World of Warcraft"); 
    HWND bot_logs_handle; 
    do {
        bot_logs_handle = FindWindow(NULL, 
                "C:\\Program Files (x86)\\World of Warcraft\\WoW.exe");
    } while (!bot_logs_handle);

    SetWindowPos(bot_logs_handle, HWND_TOP, 775, 0, 1366-765, 700, 0);
    SetWindowPos(wow_window_handle, HWND_TOP, -10, 0, 800, 600, 0);

    SetForegroundWindow(wow_window_handle);
}

void set_debug_privileges() {
    HANDLE token_handle;
    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &token_handle)) {
        printf("Could not get process token.\n");
        return;
    }

    TOKEN_PRIVILEGES tp;
    if (!LookupPrivilegeValueA(NULL, "SeDebugPrivilege", &tp.Privileges[0].Luid)) {
        printf("Could not get LUID.\n");
        return;
    }

    tp.PrivilegeCount = 1;
    tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
    
    if (!AdjustTokenPrivileges(token_handle, false, &tp, 0, (PTOKEN_PRIVILEGES)NULL, 0)) {
        printf("Could not change token's privileges.\n");
        return;
    }
}

DWORD get_proc_id_from_window_name(LPSTR window_name) {
    printf("Waiting for window...\n");
    HWND window_handle = NULL;
    while (!(window_handle = FindWindow(NULL, window_name))) Sleep(100);

    DWORD proc_id;
    GetWindowThreadProcessId(window_handle, &proc_id);
    if (!proc_id) {
        printf("Could not get process id.\n");
    }

    return proc_id;
}

BOOL inject_dll() {
    DWORD proc_id = get_proc_id_from_window_name("World of Warcraft");
    if (!proc_id) return false;

    HANDLE proc_handle = OpenProcess(PROCESS_CREATE_THREAD | 
                                     PROCESS_QUERY_INFORMATION | 
                                     PROCESS_VM_OPERATION | 
                                     PROCESS_VM_WRITE | 
                                     PROCESS_VM_READ, false, proc_id);
    if (!proc_handle) {
        printf("Could not get process handle. Check debug privileges.\n");
        return false;
    }

    LPVOID load_lib_addr = (LPVOID)GetProcAddress(
            GetModuleHandle("kernel32.dll"), "LoadLibraryA");

    size_t dll_path_len = strlen(DLL_PATH)+1;
    LPVOID p_dll_path = (LPVOID)VirtualAllocEx(
            proc_handle, NULL, dll_path_len, MEM_RESERVE|MEM_COMMIT, PAGE_READWRITE);
    WriteProcessMemory(proc_handle, p_dll_path, DLL_PATH, dll_path_len, NULL);

    HANDLE thread = CreateRemoteThread(
            proc_handle, 0, 0, 
            (LPTHREAD_START_ROUTINE)load_lib_addr, 
            (LPVOID)p_dll_path, 0, NULL);
    WaitForSingleObject(thread, INFINITE);

    CloseHandle(proc_handle);
    printf("DLL injected.\n");
    return true;
}

int main() {
    ShellExecute(NULL, "open", GAME_PATH, NULL, NULL, SW_SHOWDEFAULT);

    set_debug_privileges();
    inject_dll();

    setup_windows_layout();

    return EXIT_SUCCESS;
}
