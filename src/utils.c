#include <windows.h>
#include <stdint.h>
#include <stdio.h>

void unlock_lua() {
    char bytes_to_write[] = { 0xB8, 0x01, 0x00, 0x00, 0x00, 0xc3 };
    WriteProcessMemory(GetCurrentProcess(), 
                       (void *)0x494A50, 
                       (void*)bytes_to_write, 
                       sizeof(bytes_to_write), 
                       NULL); 
}

void create_console() {
    AllocConsole();
    FILE *file_dummy;
    freopen_s(&file_dummy, "CONOUT$", "w", stdout);
}

void setup_client() {
    sync(); // setup stuff to run code on the main thread
    unlock_lua();
    create_console();
}
