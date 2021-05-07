#include <stdint.h>
#include <stdio.h>

#include "object.h"
#include "memory_manager.h"
#include "game_functions.h"

const uint32_t OBJECT_TYPE_OFFSET = 0x14;

int n_objects;

int32_t __fastcall callback(void *thiscall_garbage, uint32_t filter, uint64_t guid) {
    object_t object;
    object.guid = guid;
    object.pointer = game_get_object_ptr(guid);
    object.object_type = read_byte(object.pointer + OBJECT_TYPE_OFFSET);

    print_object_info(object);
    n_objects++;

    return 1;
}

const char *object_type_code_to_string(enum object_type_t object_type) {
    switch (object_type) {
        case None:          return "None";
        case Item:          return "Item";
        case Container:     return "Container";
        case Unit:          return "Unit";
        case Player:        return "Player";
        case GameObject:    return "GameObject";
        case DynamicObject: return "DynamicObject";
        case Corpse:        return "Corpse";
    }
    return NULL;
}

void print_object_info(object_t object) {
    printf("Object %d\n", n_objects);
    printf("Guid: %llu\n", object.guid);
    printf("Pointer: %u\n", object.pointer);
    printf("ObjectType: %s\n\n", object_type_code_to_string(object.object_type));
}

void enumerate_visible_objects() {
    if (game_get_player_guid()) {
        n_objects = 0;
        game_enumerate_visible_objects(callback, 0);
        printf("%d Objects found.\n", n_objects);
    }
}
