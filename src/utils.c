#include <stdint.h>
// Some early version of wow have a buggy click to move functionality
// for some reason zeroing the byte at '0x860A90' solve this issue
// But the client that I'm using right now don't seemes to have this problem,
// hmm...
void fix_click_to_move() {
    uint32_t *byte = (uint32_t*)0x860A90;
    *byte = 0;
}
