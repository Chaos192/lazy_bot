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
    DWORD cur_obj = *(DWORD*)(*(DWORD*)object_manager + first_obj_ptr);
    DWORD next = cur_obj;

    wow_object_t objects[500];
    wow_unit_t units[100];

    int n_objects = 0;
    int n_units = 0;

    while (cur_obj != 0 && (cur_obj & 1) == 0) {
        if (*(DWORD*)(cur_obj+obj_type) == Unit) {
            units[n_units++] = setup_unit(cur_obj);
        } else {
            objects[n_objects++] = setup_object(cur_obj);
        }
        next = *(DWORD*)(cur_obj+next_obj_ptr);

        if (cur_obj == next) break;
        
        cur_obj = next;
    }

    for (int i = 0; i < n_objects; i++) {
        print_object_info(objects[i]);
        printf("\n");
    }

    for (int i = 0; i < n_units; i++) {
        print_unit_info(units[i]);
        printf("\n");
    }
}

wow_object_t setup_object(DWORD cur_obj) {
    wow_object_t object;
    object.guid = *(ULONGLONG*)(cur_obj+cur_obj_guid);
    object.pointer = cur_obj;
    object.type = *(DWORD*)(cur_obj+obj_type);

    return object;
}

wow_unit_t setup_unit(DWORD cur_obj) {
    wow_unit_t unit;
    unit.object = setup_object(cur_obj);

    DWORD descriptor_addr = *(DWORD*)(unit.object.pointer + descriptor_offset);
    unit.health = *(DWORD*)(descriptor_addr + health_offset);

    const char *name_pointer = (const char*)(*(DWORD*)(*(DWORD *)(unit.object.pointer + name_offset)));
    strcpy(unit.name, name_pointer);

    return unit;
}

void print_object_info(wow_object_t object) {
    printf("ObjectType: %s\n", object_type_to_string(object.type));
    printf("Guid: %llu\n", object.guid);
    printf("Pointer: 0x%u\n", object.pointer);
}

void print_unit_info(wow_unit_t unit) {
    print_object_info(unit.object);
    printf("Health: %u\n", unit.health);
    printf("Name: %s\n", unit.name);
}
