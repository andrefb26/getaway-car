#ifndef _LCOM_I8042H
#define _LCOM_I8042H

#include <lcom/lcf.h>

#define IRQ_KEYBOARD 1
#define IRQ_MOUSE    12

#define BREAK_ESC    0x81
#define TWO_BYTES    0xE0

/* KBC status register bits */
#define KBC_OBF      BIT(0)
#define KBC_IBF      BIT(1)
#define KBC_INH      BIT(4) //bit de teclado 
#define KBC_AUX      BIT(5)
#define KBC_TIMEOUT  BIT(6)
#define KBC_PARITY   BIT(7)

/* KBC ports */
#define KBC_OUTBUF_REG 0x60
#define KBC_INBUF_REG  0x60
#define KBC_STATUS_REG 0x64
#define KBC_CMD_REG    0x64

/* KBC commands */
#define KBC_READ_CMD   0x20
#define KBC_WRITE_CMD  0x60

/* Delays / retries */
#define KBC_MAX_TRIES  10
#define KBC_DELAY_US   20000

/* Mouse packet bits */
#define MOUSE_LB         BIT(0)
#define MOUSE_RB         BIT(1)
#define MOUSE_MB         BIT(2)
#define FIRST_BYTE       BIT(3)
#define MOUSE_X_SIGNAL   BIT(4)
#define MOUSE_Y_SIGNAL   BIT(5)
#define MOUSE_X_OVERFLOW BIT(6)
#define MOUSE_Y_OVERFLOW BIT(7)

/* Mouse commands */
#define WRITE_BYTE_MOUSE    0xD4
#define ENABLE_DATA_REPORT  0xF4
#define DISABLE_DATA_REPORT 0xF5
#define ENABLE_STREAM_MODE  0xEA
#define MOUSE_READ_DATA     0xEB

/* Mouse responses */
#define ACK   0xFA
#define NACK  0xFE
#define ERROR 0xFC

#endif /* _LCOM_I8042H */
