#include <windows.h>
#include <stdio.h>
#include <stdbool.h>

#include "object_manager.h"
#include "game.h"

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

    wow_object_t objects[300];
    wow_unit_t units[100];

    wow_player_t players[100];
    local_player_t local_player;

    int n_objects = 0;
    int n_units   = 0;
    int n_players = 0;

    enum object_type_t cur_obj_type;
    while (cur_obj != 0 && (cur_obj & 1) == 0) {
        cur_obj_type = *(DWORD*)(cur_obj+obj_type);
        switch (cur_obj_type) {
            case Unit: 
                units[n_units++] = setup_unit(cur_obj);
                break;
            case Player:
                if (*(ULONGLONG*)(cur_obj+cur_obj_guid) == get_player_guid()) {
                    local_player = setup_local_player(cur_obj);
                } else {
                    players[n_players++] = setup_player(cur_obj);
                }
                break;
            default:
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

    if (n_players) {
        for (int i = 0; i < n_players; i++) {
            print_object_info(players[i].object);
            printf("Name: %s\n", players[i].name);
            printf("Health: %u\n\n", players[i].health);
        }
    }

    printf("Local player found.\n");
    printf("Name: %s\n", local_player.player.name);
    printf("Health: %u\n", local_player.player.health);
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

wow_player_t setup_player(DWORD cur_obj) {
    wow_player_t player;
    player.object = setup_object(cur_obj);

    DWORD descriptor_addr = *(DWORD*)(player.object.pointer + descriptor_offset);
    player.health = *(DWORD*)(descriptor_addr + health_offset);

    DWORD name_ptr = *(DWORD*)name_base_offset;
    while (true) {
        ULONGLONG next_guid = *(DWORD*)(name_ptr + next_name_offset);
        if (next_guid == player.object.guid) break;

        name_ptr = *(DWORD*)name_ptr;
    }
    const char *player_name = (const char *)(name_ptr + player_name_offset);
    strcpy(player.name, player_name);

    return player;
}

local_player_t setup_local_player(DWORD cur_obj) {
    local_player_t local_player;
    local_player.player = setup_player(cur_obj);
    return local_player;
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
