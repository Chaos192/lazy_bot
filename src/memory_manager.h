#include <stdint.h>

uint8_t read_byte(uint32_t addr);
uint32_t read_dword(uint32_t addr);
uint64_t read_qword(uint32_t addr);
float read_float(uint32_t addr);
void write_bytes(uint32_t addr_to_write, uint8_t bytes[], size_t n_bytes);
void process_event(char *event_name);
