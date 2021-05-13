#include <windows.h>
#include <stdio.h>
#include <stdbool.h>
#include "bot.h"

bool bot_running = true;

void disable_bot() {
    bot_running = false;
}

void enable_bot() {
    bot_running = true;
}

state_t top_state() {
    if (states.top_state == -1) {
        return NO_STATE;
    }
    return states.stack[states.top_state];
}

void pop_state() {
    if (states.top_state == -1) {
        printf("State stack empty.\n");
    } else {
        states.top_state--;
    }
}

void push_state(state_t state) {
    if (states.top_state+1 == states.n_max_state) {
        printf("Can't add another state.\n");
    } else {
        states.stack[++(states.top_state)] = state;
    }
}

const char *state_to_string() {
    switch (top_state()) {
        case NO_STATE:   return "No state.\n";
        case CRY_STATE:  return "T--------T.\n";
        case YELL_STATE: return "HAAAAAAAAAAAAAA.\n";
    }
    return "";
}

void initialize_bot() {
    states.top_state = -1;
    states.n_max_state = (int)sizeof(states.stack)/sizeof(state_t);
    while (true) {
        if (bot_running) {
            printf("State: %s\n", state_to_string());
            Sleep(1000);
        }
    }
}
