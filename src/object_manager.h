typedef const DWORD offset_t;
static offset_t object_manager   = 0x00B41414;
static offset_t first_obj_ptr    = 0xac;
static offset_t cur_obj_guid     = 0x30;
static offset_t next_obj_ptr     = 0x3c;
static offset_t obj_type         = 0x14;
static offset_t descriptorOffset = 0x8;

static offset_t descriptor_offset = 0x8;
static offset_t health_offset     = 0x58;
static offset_t name_offset       = 0xB30;

static offset_t name_base_offset   = 0xC0E230;
static offset_t next_name_offset   = 0xC;
static offset_t player_name_offset = 0x14;

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
    wow_object_t object;
    DWORD health;
    char name[100];
} wow_unit_t;

typedef struct {
    wow_object_t object;
    DWORD health;
    char name[100];
} wow_player_t;

typedef struct {
    wow_player_t player;
} local_player_t ;

const char *object_type_to_string(DWORD object_type);
void enumerate_visible_objects();

wow_object_t   setup_object(DWORD cur_obj);
wow_unit_t     setup_unit(DWORD cur_obj);
wow_player_t   setup_player(DWORD cur_obj);
local_player_t setup_local_player(DWORD cur_obj);

void print_object_info(wow_object_t oject);
void print_unit_info(wow_unit_t unit);
