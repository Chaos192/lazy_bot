#include <stdint.h>

#include "object_manager.h"

void go_to(object_t local_player, position_t position) {
    uint64_t interact_guid_ptr = 0; 
    game_click_to_move(local_player.pointer, Move, &interact_guid_ptr, &position, 2);
}
