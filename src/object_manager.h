static DWORD object_manager   = 0x00B41414;
static DWORD first_obj_ptr    = 0xac;
static DWORD cur_obj_guid     = 0x30;
static DWORD next_obj_ptr     = 0x3c;
static DWORD obj_type         = 0x14;
static DWORD descriptorOffset = 0x8;

static DWORD descriptor_offset = 0x8;
static DWORD health_offset = 0x58;
static DWORD name_offset = 0xB30;

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

const char *object_type_to_string(DWORD object_type);
void enumerate_visible_objects();
wow_object_t setup_object(DWORD cur_obj);
wow_unit_t setup_unit(DWORD cur_obj);
void print_object_info(wow_object_t oject);
void print_unit_info(wow_unit_t unit);
