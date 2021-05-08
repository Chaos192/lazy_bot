#include <stdint.h>

typedef int64_t  (__cdecl* get_player_guid_ft)();
typedef uint32_t (__stdcall* get_object_ptr_ft)(uint64_t guid);
typedef uint32_t (__fastcall* enumerate_visible_objects_ft)
    (void *callback, int32_t filter); // Iterate over objects visible by the 
                                      // player and call the 'callback' for
                                      // each one of them passing their guid
                                      // as parameter.

get_player_guid_ft game_get_player_guid = (get_player_guid_ft) 0x468550;
enumerate_visible_objects_ft game_enumerate_visible_objects = 
    (enumerate_visible_objects_ft) 0x00468380;
get_object_ptr_ft game_get_object_ptr = (get_object_ptr_ft) 0x00464870;
