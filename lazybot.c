#include <windows.h>
#include <stdio.h>
#include <stdbool.h>

#include "game.h"

void iterate_object_manager() {
    DWORD object_manager = 0x00B41414;
    DWORD first_obj_ptr = 0xac;
    DWORD next_obj_ptr = 0x3c;
    DWORD obj_type = 0x14;
    DWORD descriptorOffset = 0x8;

    DWORD cur_obj = *(DWORD*)(*(DWORD*)object_manager + first_obj_ptr);
    DWORD obj_typeh = *(DWORD*)(cur_obj+obj_type);

    while (cur_obj != 0) {
        if (*(DWORD*)(cur_obj+obj_type) == 4) {
            printf("Player found.\n\n");
        }
        printf("0x%x type: %d\n", cur_obj, obj_typeh);

        cur_obj = *(DWORD*)(cur_obj+next_obj_ptr);
        obj_typeh = *(DWORD*)(cur_obj+obj_type);
        Sleep(500);
    }
}

void bot() {
    AllocConsole();
    FILE *fDummy;
    freopen_s(&fDummy, "CONOUT$", "w", stdout);

    printf("Injected...\n");

    while (true) {
        if(get_player_guid() > 0) {
            iterate_object_manager();
            break;
        }
        Sleep(500);
    }
}
