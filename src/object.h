
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

typedef struct object_t {
    uint64_t guid;
    uint32_t pointer;
    enum object_type_t object_type;
} object_t;
