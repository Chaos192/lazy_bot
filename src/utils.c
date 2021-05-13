#include <windows.h>
#include <stdint.h>

void enable_lua_api() {
    char bytes_to_write[] = { 0xB8, 0x01, 0x00, 0x00, 0x00, 0xc3 };
    WriteProcessMemory(GetCurrentProcess(), 
                       (void *)0x494A50, 
                       (void*)bytes_to_write, 
                       sizeof(bytes_to_write), 
                       NULL); 
}

void setup_client() {
    enable_lua_api();
}
