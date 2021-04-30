enum click_to_move_t {
    Move = 0x4,
};

enum object_type_t {
    None,
    Item,
    Container,
    Unit,
    Player,
    GameObject,
    DynamicObject,
    Corpse,
};

typedef struct {
    ULONGLONG guid;
    DWORD pointer;
    enum object_type_t type;
} wow_object_t;

typedef struct {
    float x;
    float y;
    float z;
} position_t;

typedef struct {
    wow_object_t object;
    DWORD health;
    char name[25];
    position_t position;
} wow_unit_t;

typedef struct {
    wow_object_t object;
    DWORD health;
    char name[13];
    position_t position;
} wow_player_t;

typedef struct {
    wow_player_t player;
} local_player_t ;

const char *object_type_to_string(DWORD object_type);
void enumerate_visible_objects();

wow_object_t   setup_object(DWORD cur_obj);
position_t     setup_position(DWORD object_p);
wow_unit_t     setup_unit(DWORD cur_obj);
wow_player_t   setup_player(DWORD cur_obj);
local_player_t setup_local_player(DWORD cur_obj);

void print_object_info(wow_object_t oject);
void print_unit_info(wow_unit_t unit);
void print_player_info(wow_player_t player);

float distance_to(position_t position);
