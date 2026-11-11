#include <lcom/lcf.h>
#include <stdint.h>
#include <stdbool.h>

#include "kbc.h"

int (util_sys_inb)(int port, uint8_t *value);

int kbc_read_outbuf(uint8_t *byte, bool mouse) {
  if (byte == NULL) return 1;

  uint8_t status;

  for (int i = 0; i < KBC_MAX_TRIES; i++) {
    if (util_sys_inb(KBC_STATUS_REG, &status) != OK)
      return 1;

    if (status & KBC_OBF) {

      if (status & (KBC_PARITY | KBC_TIMEOUT))
        return 1;

      if (mouse && !(status & KBC_AUX))
        return 1;

      if (!mouse && (status & KBC_AUX))
        return 1;

      if (util_sys_inb(KBC_OUTBUF_REG, byte) != OK)
        return 1;

      return 0;
    }

    tickdelay(micros_to_ticks(KBC_DELAY_US));
  }

  return 1;
}

int kbc_write_cmd(uint8_t port, uint8_t cmd) {
  uint8_t status;

  for (int i = 0; i < KBC_MAX_TRIES; i++) {
    if (util_sys_inb(KBC_STATUS_REG, &status) != OK) {
      return 1;
    }

    if ((status & KBC_IBF) == 0) {
      if (sys_outb(port, cmd) != OK) {
        return 1;
      }

      return 0;
    }

    tickdelay(micros_to_ticks(KBC_DELAY_US));
  }

  return 1;
}
