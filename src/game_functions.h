#include <stdint.h>

enum click_type_t {
    Move = 0x4,
};

typedef int64_t  (__cdecl* get_player_guid_ft)();
typedef uint32_t (__stdcall* get_object_ptr_ft)(uint64_t guid);
typedef uint32_t (__fastcall* enumerate_visible_objects_ft)
    (void *callback, int32_t filter); // Iterate over objects visible by the 
                                      // player and call the 'callback' for
                                      // each one of them passing their guid
                                      // as parameter.
typedef void (__fastcall* click_to_move_ft)
    (void *thiscall_garbage, int32_t player_ptr, enum click_type_t click_type, 
     uint64_t *interact_guid_ptr, position_t *position_ptr, float precision);

get_player_guid_ft game_get_player_guid = (get_player_guid_ft) 0x468550;
enumerate_visible_objects_ft game_enumerate_visible_objects = 
    (enumerate_visible_objects_ft) 0x00468380;
get_object_ptr_ft game_get_object_ptr = (get_object_ptr_ft) 0x00464870;
click_to_move_ft game_click_to_move = (click_to_move_ft) 0x00611130;
