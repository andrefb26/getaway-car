#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "i8254.h"

int counter=0 ; //contador global  dos interrupts

int hook_id=0; //id da subscrição

int(timer_set_frequency)(uint8_t timer, uint32_t freq) {
    if (timer > 2) return 1;
    if (freq < 19 || freq > TIMER_FREQ) return 1;

    //lê a configuração atual do timer
    uint8_t conf;
    if (timer_get_conf(timer, &conf) != 0) return 1;

    // calcula o divisor
    uint16_t divider = (uint16_t)(TIMER_FREQ / freq);

    // Constrói o Control Word
    // Bits 7-6: seleciona o timer
    // Bits 5-4: 11 = LSB seguido de MSB
    // Bits 3-0: preservar da configuração atual (counting mode + BCD)
    uint8_t ctrl = (timer << 6) | TIMER_LSB_MSB | (conf & 0x0F);

    // Seleciona a porta do timer
    uint8_t port;
    if      (timer == 0) port = TIMER_0;
    else if (timer == 1) port = TIMER_1;
    else                 port = TIMER_2;

    // escreve o Control Word no Control Register
    if (sys_outb(TIMER_CTRL, ctrl) != 0) return 1;

    // Escreve LSB e MSB do divisor
    uint8_t lsb, msb;
    if (util_get_LSB(divider, &lsb) != 0) return 1;
    if (util_get_MSB(divider, &msb) != 0) return 1;

    if (sys_outb(port, lsb) != 0) return 1;
    if (sys_outb(port, msb) != 0) return 1;

    return 0;
}

int(timer_subscribe_int)(uint8_t *bit_no) {
    *bit_no = hook_id;
    return sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE, &hook_id);
}

int(timer_unsubscribe_int)() {
    return sys_irqrmpolicy(&hook_id);
}

void(timer_int_handler)() {
    counter++;
}

int timer_get_counter() {
    return counter;
}


int (timer_get_conf)(uint8_t timer, uint8_t *st) {
  if (timer > 2) return 1;

    // read-back command: bit7=1, bit6=1, bit5=0 (latch status),
    // bits 3-1 selecionam o timer
    uint8_t cmd = TIMER_RB_CMD          // 0xC0
                | TIMER_RB_COUNT_       // não latch count (bit5=1 -> desativar)
                | TIMER_RB_SEL(timer);  // seleciona o timer
    if (sys_outb(TIMER_CTRL, cmd) != 0) return 1;
    // lê o status byte da porta do timr selecionado
    uint8_t port;
    if      (timer == 0) port = TIMER_0;
    else if (timer == 1) port = TIMER_1;
    else                 port = TIMER_2;

    return util_sys_inb(port, st);
}


int (timer_display_conf)(uint8_t timer, uint8_t conf, enum timer_status_field field) {
  //parseia e imprime o campo pedido
    union timer_status_field_val val;
      switch (field) {
        case tsf_all:
            val.byte = conf;
            break;

        case tsf_initial: {
            uint8_t init = (conf >> 4) & 0x03;
            if      (init == 1) val.in_mode = LSB_only;
            else if (init == 2) val.in_mode = MSB_only;
            else if (init == 3) val.in_mode = MSB_after_LSB;
            else                val.in_mode = INVAL_val;
            break;
        }

        case tsf_mode:
            val.count_mode = (conf >> 1) & 0x07;
            if (val.count_mode > 5) val.count_mode &= 0x03;
            break;

        case tsf_base:
            val.bcd = (bool)(conf & 0x01);
            break;

        default:
            return 1;
    }

    return timer_print_config(timer, field, val);
    //o header tem esta função implementada
}

