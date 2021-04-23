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
    enum object_type_t object_type;
} wow_object_t;

typedef struct {
    ULONGLONG guid;
    DWORD pointer;
    enum object_type_t object_type;
    DWORD health;
    char unit_name[100];
} wow_unit_t;

void set_unit_health(wow_unit_t *wow_unit);
const char *object_type_to_string(DWORD object_type);
void enumerate_visible_objects();
