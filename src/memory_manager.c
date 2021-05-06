#include <stdint.h>

uint8_t read_byte(uint32_t addr) {
    return *(uint8_t *)addr;
}
