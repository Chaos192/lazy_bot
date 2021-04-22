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
} object_t;

const char *object_type_to_string(DWORD object_type);
void iterate_object_manager();
