#include <stdint.h>

#include "object.h"

const uint32_t OBJECT_TYPE_OFFSET = 0x14;

int32_t callback(int32_t filter, uint64_t guid) {
    uint32_t object_pointer = game_object_ptr(guid);
    object_type_t object_type = 
        (object_type_t)read_byte(object_pointer + OBJECT_TYPE_OFFSET);
}

void enumarate_visible_objects() {
    if (game_get_player_guid()) {
        game_enumerate_visible_objects(callback, 0);
    }
}
