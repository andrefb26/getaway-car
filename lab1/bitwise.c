#include "bitwise.h"
#include <stdarg.h>

uint8_t clear(uint8_t msk, int pos) {
    return msk & ~(1 << pos);
}

uint8_t set(uint8_t msk, int pos) {
    return msk |(1 << pos);
}

bool is_set(uint8_t msk, int pos) {
    return (msk &(1 << pos)) != 0;
}

uint8_t lsb(uint16_t wide_msk) {
    return (uint8_t)wide_msk;
}

uint8_t msb(uint16_t wide_msk) {
    return (uint8_t)(wide_msk >> 8);
}

uint8_t mask(int pos, ...) {
    uint8_t res = 0;
    va_list ap;
    va_start(ap, pos);
    while (pos != MSK_END) {
        res = set(res, pos);
        pos = va_arg(ap, int);  
    }
    va_end(ap);
    return res;
}

