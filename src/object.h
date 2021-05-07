
enum object_type_t {
    None          = 0x0,
    Item          = 0x1,
    Container     = 0x2,
    Unit          = 0x3,
    Player        = 0x4,
    GameObject    = 0x5,
    DynamicObject = 0x6,
    Corpse        = 0x7,
};

typedef struct object_t {
    uint64_t guid;
    uint32_t pointer;
    enum object_type_t object_type;
} object_t;

typedef struct objects_t {
    uint32_t n_objects;
    object_t objects[215];
} objects_t;

objects_t game_objects;
