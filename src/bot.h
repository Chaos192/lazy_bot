#include <stdbool.h>

typedef enum {
    NO_STATE,
    CRY_STATE,
    YELL_STATE,
} state_t;

typedef struct {
    int n_max_state;
    int top_state;
    state_t stack[10]; 
} current_states_t;

current_states_t states;
static bool bot_running;

void initialize_bot();
const char *state_to_string();
