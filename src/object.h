
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

typedef struct {
    float x;
    float y;
    float z;
} position_t;

typedef struct {
    uint64_t guid;
    uint32_t pointer;
    uint32_t health;
    char *name_ptr;
    position_t position;
    enum object_type_t type;
} object_t;

void print_object_info(object_t *object);
