#include <stdint.h>
#include <stdio.h>

#include "object.h"
#include "memory_manager.h"
#include "game_functions.h"

const uint32_t OBJECT_TYPE_OFFSET = 0x14;

int32_t __fastcall callback(void *thiscall_garbage, uint32_t filter, uint64_t guid) {
    object_t object;
    object.guid = guid;
    object.pointer = game_get_object_ptr(guid);
    object.object_type = read_byte(object.pointer + OBJECT_TYPE_OFFSET);

    game_objects.objects[game_objects.n_objects++] = object;

    return 1;
}

char *object_type_code_to_string(enum object_type_t object_type) {
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

void print_found_objects() {
    object_t *obj_p;
    printf("%d objects found:\n", game_objects.n_objects);
    for (int i = 0; i < game_objects.n_objects; i++) {
        obj_p = &game_objects.objects[i];
        printf("Object %d\n", i+1);
        printf("Guid: %llu\n", obj_p->guid);
        printf("Pointer: %u\n", obj_p->pointer);
        printf("ObjectType: %s\n\n", object_type_code_to_string(obj_p->object_type));
    }
}

void enumerate_visible_objects() {
    if (game_get_player_guid()) {
        game_objects.n_objects = 0;
        game_enumerate_visible_objects(callback, 0);
        print_found_objects();
    }
}
