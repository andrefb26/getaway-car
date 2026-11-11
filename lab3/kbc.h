//
// Created by conduto on 4/10/26.
//
#ifndef LAB3_KBC_H
#define LAB3_KBC_H

#include <stdint.h>
#include <stdbool.h>

#define OK              0
#define KBC_IRQ         1    // Keyboard Interrupt Channel

/* Status Register Bits */
#define KBC_OBF       BIT(0)  // Output Buffer Full - Dados prontos para ler
#define KBC_IBF       BIT(1)  // Input Buffer Full - Não escrever se estiver a 1
#define KBC_AUX       BIT(5)  // Mouse Data - Se estiver a 1, os dados são do rato
#define KBC_TIMEOUT   BIT(6)  // Timeout Error - Bit 6
#define KBC_PARITY    BIT(7)  // Parity Error - Bit 7

#define KBC_OUTBUF_REG  0x60 // read    Output Buffer    - Read scancodes or returned values from KBC commands
#define KBC_INBUF_REG   0x60 // write   Input Buffer     - Write arguments of KBC commands
#define KBC_STATUS_REG  0x64 // read    Status Register  - Read the KBC status
#define KBC_CMD_REG     0x64 // write   Command Register - Write KBC commands

#define KBC_MAX_TRIES   10
#define KBC_DELAY_US    20000  // 20ms entre tentativas

#define KBC_READ_CMD    0x20   // ler command byte
#define KBC_WRITE_CMD   0x60   // escrever command byte
#define KBC_INT_BIT     (1<<0) // bit de interrupção no command byte

#define ESC_BREAKCODE   0x81
#define SCANCODE_2BYTE  0xE0   // prefixo de scancode 2 bytes


int kbc_read_outbuf(uint8_t *byte, bool mouse);
int kbc_write_cmd(uint8_t port, uint8_t cmd);
int kbc_write_arg(uint8_t arg);
int kbc_subscribe_int(uint8_t *bit_no);
int kbc_unsubscribe_int();
void (kbc_ih)();
uint8_t get_current_scancode();
bool check_kbc_error();
uint32_t get_sys_inb_counter();

/*
    STATUS REGISTER BYTE

    Os bits 7 e 6 devem ser sempre verificados no Interrupt Handler,
    uma vez que sinalizam erros de comunicação entre o teclado e o KBC.
    Mesmo que ocorra um erro, o Output Buffer deve ser sempre lido, mas o valor deve
    ser descartado.

*/
#endif //LAB3_KBC_H
