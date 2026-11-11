#ifndef LAB4_KBC_H
#define LAB4_KBC_H

#include <lcom/lcf.h>
#include <stdint.h>
#include <stdbool.h>
#include "i8042.h"

int kbc_read_outbuf(uint8_t *byte, bool mouse);
int kbc_write_cmd(uint8_t port, uint8_t cmd);

#endif
