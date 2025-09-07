#include <stdint.h>

// simulate transformation : 'A' -> 'a', 'B' -> 'b', ...
uint8_t foo(uint8_t c) {
    return c + 0x20;  // simple 'A'→'a' etc.
}
