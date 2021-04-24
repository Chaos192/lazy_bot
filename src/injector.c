#include <windows.h>
#include <stdio.h>
#include <stdbool.h>

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

    return proc_id;
}

BOOL inject_dll(DWORD proc_id, LPSTR dll_path) {
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

    LPVOID load_lib_addr = (LPVOID)GetProcAddress(GetModuleHandle("kernel32.dll"), "LoadLibraryA");

    LPVOID p_dll_path = (LPVOID)VirtualAllocEx(proc_handle, NULL, strlen(dll_path)+1, MEM_RESERVE|MEM_COMMIT, PAGE_READWRITE);
    WriteProcessMemory(proc_handle, p_dll_path, dll_path, strlen(dll_path)+1, NULL);

    HANDLE thread = CreateRemoteThread(proc_handle, NULL, NULL, (LPTHREAD_START_ROUTINE)load_lib_addr, (LPVOID)p_dll_path, NULL, NULL);
    WaitForSingleObject(thread, INFINITE);

    CloseHandle(proc_handle);
    return true;
}

int main() {
    LPSTR game_path = "\"C:\\Program Files (x86)\\World of Warcraft\\WoW.exe\"";
    ShellExecute(NULL, "open", game_path, NULL, NULL, SW_SHOWDEFAULT);

    set_debug_privileges();

    DWORD proc_id = get_proc_id_from_window_name("World of Warcraft");
	LPSTR dll_path = "C:\\Users\\Felipe David\\fun\\lazybot\\bin\\lazybot.dll";
    if (!inject_dll(proc_id, dll_path)) {
        printf("Could not inject the dll.\n"); 
        return EXIT_FAILURE;
    }

    printf("DLL Injected.\n"); 
    return EXIT_SUCCESS;
}
