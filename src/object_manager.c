#include <stdint.h>
#include <stdio.h>

#include "object.h"
#include "memory_manager.h"
#include "game_functions.h"

const uint32_t OBJECT_TYPE_OFFSET = 0x14;

int32_t __fastcall callback(void *thiscall_garbage, uint32_t filter, uint64_t guid) {
    uint32_t object_pointer = game_get_object_ptr(guid);
    enum object_type_t object_type = read_byte(object_pointer + OBJECT_TYPE_OFFSET);

    return 1;
}

void enumerate_visible_objects() {
    if (game_get_player_guid()) {
        game_enumerate_visible_objects(callback, 0);
    }
}
