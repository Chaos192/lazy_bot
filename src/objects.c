#include <windows.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include "objects.h"
#include "game.h"

static local_player_t local_player;

wow_object_t setup_object(DWORD cur_obj) {
    wow_object_t object;
    object.guid = *(ULONGLONG*)(cur_obj+CUR_OBJ_GUID);
    object.pointer = cur_obj;
    object.type = *(DWORD*)(cur_obj+OBJ_TYPE);

    return object;
}

position_t setup_position(DWORD object_p) {
    position_t position;
    position.x = *(float *)(object_p + POS_X_OFFSET);
    position.y = *(float *)(object_p + POS_Y_OFFSET);
    position.z = *(float *)(object_p + POS_Z_OFFSET);
    return position;
}

wow_unit_t setup_unit(DWORD cur_obj) {
    wow_unit_t unit;
    unit.object = setup_object(cur_obj);

    DWORD descriptor_addr = *(DWORD*)(unit.object.pointer + DESCRIPTOR_OFFSET);
    unit.health = *(DWORD*)(descriptor_addr + HEALTH_OFFSET);

    const char *name_pointer = 
        (const char*)(*(DWORD*)(*(DWORD *)(unit.object.pointer + NAME_OFFSET)));
    strcpy(unit.name, name_pointer);

    unit.position = setup_position(unit.object.pointer);

    return unit;
}

wow_player_t setup_player(DWORD cur_obj) {
    wow_player_t player;
    player.object = setup_object(cur_obj);

    DWORD descriptor_addr = *(DWORD*)(player.object.pointer + DESCRIPTOR_OFFSET);
    player.health = *(DWORD*)(descriptor_addr + HEALTH_OFFSET);

    DWORD name_ptr = *(DWORD*)NAME_BASE_OFFSET;
    while (true) {
        ULONGLONG next_guid = *(DWORD*)(name_ptr + NEXT_NAME_OFFSET);
        if (next_guid == player.object.guid) break;

        name_ptr = *(DWORD*)name_ptr;
    }
    const char *player_name = (const char *)(name_ptr + PLAYER_NAME_OFFSET);
    strcpy(player.name, player_name);

    player.position = setup_position(player.object.pointer);

    return player;
}

local_player_t setup_local_player(DWORD cur_obj) {
    local_player_t local_player;
    local_player.player = setup_player(cur_obj);
    return local_player;
}

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

void print_object_info(wow_object_t object) {
    printf("ObjectType: %s\n", object_type_to_string(object.type));
    printf("Guid: %llu\n", object.guid);
    printf("Pointer: 0x%x\n", object.pointer);
}

void print_unit_info(wow_unit_t unit) {
    print_object_info(unit.object);
    printf("Health: %u\n", unit.health);
    printf("Position: X: %f, Y: %f, Z: %f\n", unit.position.x, 
                                              unit.position.y,
                                              unit.position.z);
    printf("Name: %s\n", unit.name);
}

void print_player_info(wow_player_t player) {
    print_object_info(player.object);
    printf("Health: %u\n", player.health);
    printf("Position: X: %f, Y: %f, Z: %f\n", player.position.x, 
                                              player.position.y,
                                              player.position.z);
    printf("Name: %s\n", player.name);
}

// determines the distance between the local_player and the specified position
float distance_to(position_t position) {
    float delta_x = local_player.player.position.x - position.x;
    float delta_y = local_player.player.position.y - position.y;
    float delta_z = local_player.player.position.z - position.z;

    return (float) sqrt(delta_x*delta_x + delta_y*delta_y + delta_z*delta_z);
}

void enumerate_visible_objects() {
    DWORD cur_obj = *(DWORD*)(*(DWORD*)OBJECT_MANAGER + FIRST_OBJ_PTR);
    DWORD next = cur_obj;

    wow_object_t objects[300];
    wow_unit_t units[100];

    wow_player_t players[100];

    int n_objects = 0;
    int n_units   = 0;
    int n_players = 0;

    enum object_type_t cur_obj_type;
    while (cur_obj != 0 && (cur_obj & 1) == 0) {
        cur_obj_type = *(DWORD*)(cur_obj+OBJ_TYPE);
        switch (cur_obj_type) {
            case Unit: 
                units[n_units++] = setup_unit(cur_obj);
                break;
            case Player:
                if (*(ULONGLONG*)(cur_obj+CUR_OBJ_GUID) == get_player_guid()) {
                    local_player = setup_local_player(cur_obj);
                } else {
                    players[n_players++] = setup_player(cur_obj);
                }
                break;
            default:
                objects[n_objects++] = setup_object(cur_obj);
        }

        next = *(DWORD*)(cur_obj+NEXT_OBJ_PTR);
        if (cur_obj == next) break;
        
        cur_obj = next;
    }

    if (n_units > 1) {
    wow_unit_t closest_unit = units[0];
    float closest_unit_distance = distance_to(closest_unit.position);
    float unit_distance;
    for (int i = 1; i < n_units; i++) {
        unit_distance =  distance_to(units[i].position);
        if (unit_distance < closest_unit_distance) {
            closest_unit = units[i];
            closest_unit_distance = unit_distance;
        }
    }

    printf("Closest uint:\n");
    print_unit_info(closest_unit);
    printf("Distance: %f\n", closest_unit_distance);
    }
    

    //for (int i = 0; i < n_objects; i++) {
    //    print_object_info(objects[i]);
    //    printf("\n");
    //}

    //for (int i = 0; i < n_units; i++) {
    //    print_unit_info(units[i]);
    //    printf("\n");
    //}

    //if (n_players) {
    //    for (int i = 0; i < n_players; i++) {
    //        print_player_info(players[i]);
    //    }
    //}

    //printf("Local player found.\n");
    //print_player_info(local_player.player);
}
