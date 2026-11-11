#include <lcom/lcf.h>
#include <stdint.h>
#include "kbc.h"

static int kbc_hook_id = 1;
static uint8_t current_scancode = 0;
static bool has_error = false;

int kbc_subscribe_int(uint8_t *bit_no) {
    if (bit_no == NULL) return 1; // check ponteiro
    kbc_hook_id=1;
    *bit_no = kbc_hook_id; // guardar bit

    if (sys_irqsetpolicy(KBC_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &kbc_hook_id) != OK) return 1;
    // EXCLUSIVE STEALS THE KEYBOARD FOR US

    return 0;
}

int kbc_unsubscribe_int() {
    if (sys_irqrmpolicy(&kbc_hook_id) != OK) return 1; // remover interrupções
    return 0;
}

void (kbc_ih)() {
    uint8_t status;
    has_error = false;

    // ler status register
    if (util_sys_inb(KBC_STATUS_REG, &status) != OK) {
        has_error = true;
        return;
    }

    // ler output buffer
    if (util_sys_inb(KBC_OUTBUF_REG, &current_scancode) != OK) {
        has_error = true;
        return;
    }

    // errors
    if (status & (KBC_PARITY | KBC_TIMEOUT)) {
        has_error = true;
    }
}

uint8_t get_current_scancode() {
    return current_scancode;
}

bool check_kbc_error() {
    return has_error;
}


// Lê um byte do Output Buffer
// mouse=true: espera dados do rato (AUX=1); mouse=false: espera dados do teclado (AUX=0)
int kbc_read_outbuf(uint8_t *byte, bool mouse) {
    uint8_t status;

    for (int i = 0; i < KBC_MAX_TRIES; i++) {
        if (util_sys_inb(KBC_STATUS_REG, &status) != OK) return -1;

        if (status & KBC_OBF) {
            if (util_sys_inb(KBC_OUTBUF_REG, byte) != OK) return -1;

            if (status & (KBC_PARITY | KBC_TIMEOUT)) return -1;

            if ( mouse && !(status & KBC_AUX)) return -1; // esperava rato, veio teclado
            if (!mouse &&  (status & KBC_AUX)) return -1; // esperava teclado, veio rato

            return OK;
        }

        tickdelay(micros_to_ticks(KBC_DELAY_US));
    }
    return -1; // Timeout
}

// Escreve um comando no porto KBC indicado (espera IBF estar livre)
int kbc_write_cmd(uint8_t port, uint8_t cmd) {
    uint8_t status;
    uint32_t tries = 0;

    while (tries < KBC_MAX_TRIES) {
        if (util_sys_inb(KBC_STATUS_REG, &status) != OK) return 1;

        if (!(status & KBC_IBF)) {
            return sys_outb(port, cmd);
        }

        tickdelay(micros_to_ticks(KBC_DELAY_US));
        tries++;
    }
    return 1; // timeout
}

// Escreve um argumento no Input Buffer (espera IBF estar livre)
int kbc_write_arg(uint8_t arg) {
    uint8_t status;
    uint32_t tries = 0;

    while (tries < KBC_MAX_TRIES) {
        if (util_sys_inb(KBC_STATUS_REG, &status) != OK) return 1;

        if (!(status & KBC_IBF)) {
            // Se o bit IBF não está ativo, o buffer está livre para escrita
            return sys_outb(KBC_INBUF_REG, arg);
        }
        tickdelay(micros_to_ticks(KBC_DELAY_US));
        tries++;
    }
    return 1;
}

