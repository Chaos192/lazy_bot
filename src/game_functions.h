#include <stdint.h>

typedef int64_t  (__cdecl* get_player_guid_ft)();
typedef uint32_t (__fastcall* enumerate_visible_objects_ft)
    (uint32_t callback, int filter, uint32_t ptr);
typedef uint32_t (__fastcall* get_object_ptr_ft)(uint64_t guid);

get_player_guid_ft game_get_player_guid = (get_player_guid_ft) 0x468550;
enumerate_visible_objects_ft game_enumerate_visiable_objects = 
    (enumerate_visible_objects_ft) 0x00468380;
get_object_ptr_ft game_get_object_ptr = (get_object_ptr_ft) 0x00468460;
