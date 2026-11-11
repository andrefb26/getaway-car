#include <lcom/lcf.h>

#include <lcom/lab3.h>
#include "kbc.h"

#include <stdbool.h>
#include <stdint.h>

int main(int argc, char *argv[]) {
    //language of LCF messages
    lcf_set_language("EN-US");

    // enables to log function invocations that are being "wrapped" by LCF
    lcf_trace_calls("/home/lcom/labs/lab3/trace.txt");

    // enables to save the output of printf function calls on a file
    lcf_log_output("/home/lcom/labs/lab3/output.txt");

    // [LCF handles command line arguments and invokes the right function]
    if (lcf_start(argc, argv))
        return 1;

    // LCF clean up tasks
    lcf_cleanup();

    return 0;
}

// Lê e imprime scancodes do teclado usando interrupções (IRQ1).
int (kbd_test_scan)() {
    int ipc_status;
    message msg;
    uint8_t irq_set;

    if (kbc_subscribe_int(&irq_set) != 0) return 1;

    uint8_t bytes[2]; //scancode
    uint8_t size = 0; //bytes recolhidos
    bool two_bytes = false;
    bool done = false;

    while (!done) {
        //kernel
        if (driver_receive(ANY, &msg, &ipc_status) != 0)
            continue;
        //only hardware
        if (is_ipc_notify(ipc_status) && _ENDPOINT_P(msg.m_source) == HARDWARE) {
            //
            if (msg.m_notify.interrupts & BIT(irq_set)) {
                kbc_ih();

                if (check_kbc_error())
                    continue;

                uint8_t data = get_current_scancode();

                // Prefixo de scancode de 2 bytes
                if (data == 0xE0) {
                    two_bytes = true;
                    bytes[0] = data;
                    size = 1;
                }

                // Byte final (ou único) do scancode
                else {
                    if (two_bytes) {
                        bytes[1] = data;
                        size = 2;
                        two_bytes = false;
                    } else {
                        bytes[0] = data;
                        size = 1;
                    }

                    bool make = !(bytes[size - 1] & BIT(7));
                    kbd_print_scancode(make, size, bytes);

                    //esc
                    if (size == 1 && bytes[0] == 0x81)
                        done = true;
                }
            }
        }
    }
    if (kbc_unsubscribe_int() != 0)
        return 1;

    return 0;
}


//Lê e imprime scancodes do teclado usando polling (sem interrupções).
int (kbd_test_poll)() {
    uint8_t cmd_byte;
    if (kbc_write_cmd(KBC_CMD_REG, KBC_READ_CMD) != OK) return 1;
    if (kbc_read_outbuf(&cmd_byte, false) != OK) return 1;
    uint8_t cmd_byte_without_kbd_int = cmd_byte & ~KBC_INT_BIT;
    if (kbc_write_cmd(KBC_CMD_REG, KBC_WRITE_CMD) != OK) return 1;
    if (kbc_write_arg(cmd_byte_without_kbd_int) != OK) return 1;


    uint8_t scancode_bytes[2];
    uint8_t size = 0;
    bool done = false;

    while (!done) {
        uint8_t byte;

        // Tentar ler um byte
        if (kbc_read_outbuf(&byte, false) != OK) continue;

        if (size == 0 && byte == SCANCODE_2BYTE) {
            //1 byte, guardar e esperar pelo 2º
            scancode_bytes[0] = byte;
            size = 1;
        } else {
            // Byte final/unico
            scancode_bytes[size] = byte;
            size++;

            bool is_make = !(byte & 0x80); // bit 7 = 0 → makecode,bit 7 = 1 → breakcode
            kbd_print_scancode(is_make, size, scancode_bytes);

            // Verificar se é o breakcode do ESC
            if (size == 1 && byte == ESC_BREAKCODE) {
                done = true;
            }

            size = 0; // reset
        }
    }

    // reativa interrupções
    if (kbc_write_cmd(KBC_CMD_REG, KBC_WRITE_CMD) != OK) return 1;
    if (kbc_write_arg(cmd_byte) != OK) return 1;

    return 0;
}

int(kbd_test_timed_scan)(uint8_t n) {

    int ipc_status;
    uint8_t timer_bit_no, kbc_bit_no;
    message msg;
    uint32_t timer_ticks = 0;
    bool done = false;
    bool two_bytes = false;
    uint8_t bytes[2];
    uint8_t size = 0;

    if (timer_subscribe_int(&timer_bit_no) != 0) return 1;
    if (kbc_subscribe_int(&kbc_bit_no) != 0) {
      timer_unsubscribe_int();
      return 1;
    }

    const uint32_t irq_set_timer = BIT(timer_bit_no);
    const uint32_t irq_set_kbc = BIT(kbc_bit_no);
    const uint32_t timeout_ticks = (uint32_t) n * sys_hz();

    while (!done && timer_ticks < timeout_ticks) {
      if (driver_receive(ANY, &msg, &ipc_status) != 0)
        continue;

      if (!is_ipc_notify(ipc_status))
        continue;

      if (_ENDPOINT_P(msg.m_source) != HARDWARE)
        continue;

      if (msg.m_notify.interrupts & irq_set_kbc) {
        kbc_ih();

        if (!check_kbc_error()) {
          uint8_t data = get_current_scancode();
          timer_ticks = 0;

          if (data == SCANCODE_2BYTE) {
            two_bytes = true;
            bytes[0] = data;
            size = 1;
          } else {
            if (two_bytes) {
              bytes[1] = data;
              size = 2;
              two_bytes = false;
            } else {
              bytes[0] = data;
              size = 1;
            }

            bool make = !(bytes[size - 1] & BIT(7));
            kbd_print_scancode(make, size, bytes);

            if (size == 1 && bytes[0] == ESC_BREAKCODE)
              done = true;
          }
        }
      }

      if (msg.m_notify.interrupts & irq_set_timer) {
        timer_int_handler();
        timer_ticks++;
      }
    }

    if (timer_unsubscribe_int() != 0) return 1;
    if (kbc_unsubscribe_int() != 0) return 1;
    if (kbd_print_no_sysinb(get_sys_inb_counter()) != 0) return 1;

    return 0;
}
