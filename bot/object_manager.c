#include <windows.h>
#include <stdio.h>

#include "object_manager.h"

const char *object_type_to_string(DWORD object_type) {
    const char *string;
    switch (object_type) {
        case None:          string = "None";         break;
        case Item:          string = "Item";         break;
        case Container:     string = "Container";    break;
        case Unit:          string = "Unit";         break;
        case Player:        string = "Player";       break;
        case GameObject:    string = "GameObject";   break;
        case DynamicObject: string = "DynamiObject"; break;
        case Corpse:        string = "Corpse";       break;
        default: string = "";
    }
    return string;
}

void enumerate_visible_objects() {
    static DWORD object_manager   = 0x00B41414;
    static DWORD first_obj_ptr    = 0xac;
    static DWORD cur_obj_guid     = 0x30;
    static DWORD next_obj_ptr     = 0x3c;
    static DWORD obj_type         = 0x14;
    static DWORD descriptorOffset = 0x8;

    DWORD cur_obj = *(DWORD*)(*(DWORD*)object_manager + first_obj_ptr);
    DWORD next = cur_obj;

    wow_object_t objects[500];
    wow_unit_t units[100];

    int n_objects = 0;
    int n_units = 0;

    while (cur_obj != 0 && (cur_obj & 1) == 0) {
        if (*(DWORD*)(cur_obj+obj_type) == Unit) {
            wow_unit_t* unit_p = &units[n_units];
            unit_p->guid = *(ULONGLONG*)(cur_obj+cur_obj_guid);
            unit_p->pointer = cur_obj;
            unit_p->object_type = *(DWORD*)(cur_obj+obj_type);
            set_unit_health(unit_p);
            n_units++;
        } else {
            objects[n_objects].guid = *(ULONGLONG*)(cur_obj+cur_obj_guid);
            objects[n_objects].pointer = cur_obj;
            objects[n_objects++].object_type = *(DWORD*)(cur_obj+obj_type);
        }
        next = *(DWORD*)(cur_obj+next_obj_ptr);

        if (cur_obj == next) break;
        
        cur_obj = next;
    }

    
    printf("%d objects found:\n", n_objects);
    for (int i = 0; i < n_objects != 0; i++) {
        printf("Guid: %llu\n", objects[i].guid);
        printf("Pointer: 0x%x\n", objects[i].pointer);
        printf("ObjectType: %s\n\n", object_type_to_string(objects[i].object_type));
    }

    printf("Printing units:\n");
    for (int i = 0; i < n_units; i++) {
        wow_unit_t* unit_p = &units[i];
        printf("Guid: %llu\n", unit_p->guid);
        printf("Pointer: 0x%x\n", unit_p->pointer);
        printf("ObjectType: %s\n", object_type_to_string(unit_p->object_type));
        printf("Health: %u\n", unit_p->health);
        printf("Name: %s\n\n", unit_p->unit_name);
    }
}

void set_unit_health(wow_unit_t *wow_unit) {
    static DWORD descriptor_offset = 0x8;
    static DWORD health_offset = 0x58;
    static DWORD name_offset = 0xB30;

    DWORD descriptor_addr = *(DWORD*)(wow_unit->pointer + descriptor_offset);
    DWORD health_addr = descriptor_addr + health_offset;
    wow_unit->health = *(DWORD*)health_addr;

    const char *name_pointer = (char *)(descriptor_addr + name_offset);
    strcpy(wow_unit->unit_name, name_pointer);
}
