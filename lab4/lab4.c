// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>
#include <stdint.h>
#include <stdio.h>
#include "i8042.h"

// Any header files included below this line should have been created by you
#include "mouse.h"
#include "timer.h"

extern int counter;
int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need/ it]
  lcf_trace_calls("/home/lcom/labs/lab4/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab4/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int (mouse_test_packet)(uint32_t cnt) {
  uint8_t mouse_bit_no;
  int ipc_status;
  message msg;
  uint32_t packets_read = 0;

  if (mouse_subscribe_int(&mouse_bit_no) != 0)
    return 1;

  if (mouse_write(ENABLE_DATA_REPORT) != 0) {
    mouse_unsubscribe_int();
    return 1;
  }

  int irq_set_mouse = BIT(mouse_bit_no);

  while (packets_read < cnt) {
    if (driver_receive(ANY, &msg, &ipc_status) != 0)
      continue;

    if (is_ipc_notify(ipc_status)) {
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:
          if (msg.m_notify.interrupts & irq_set_mouse) {
            mouse_ih();

            if (mouse_packet_ready()) {
              mouse_bytes_to_packet();
              mouse_print_packet(get_mouse_packet());
              packets_read++;
            }
          }
          break;
        default:
          break;
      }
    }
  }

  if (mouse_write(DISABLE_DATA_REPORT) != 0) {
    mouse_unsubscribe_int();
    return 1;
  }

  if (mouse_unsubscribe_int() != 0)
    return 1;

  return 0;
}

int (mouse_test_async)(uint8_t idle_time) {
  uint8_t mouse_bit_no, timer_bit_no;
  int ipc_status;
  message msg;
  int hz = (int) sys_hz();

  if (mouse_subscribe_int(&mouse_bit_no) != 0)
    return 1;

  if (timer_subscribe_int(&timer_bit_no) != 0) {
    mouse_unsubscribe_int();
    return 1;
  }

  if (mouse_write(ENABLE_DATA_REPORT) != 0) {
    timer_unsubscribe_int();
    mouse_unsubscribe_int();
    return 1;
  }

  int irq_set_mouse = BIT(mouse_bit_no);
  int irq_set_timer = BIT(timer_bit_no);

  counter = 0;

  while (counter< idle_time * hz) {
    if (driver_receive(ANY, &msg, &ipc_status) != 0)
      continue;

    if (is_ipc_notify(ipc_status)) {
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:
          if (msg.m_notify.interrupts & irq_set_timer) {
            timer_int_handler();
          }

          if (msg.m_notify.interrupts & irq_set_mouse) {
            mouse_ih();

            if (mouse_packet_ready()) {
              mouse_bytes_to_packet();
              mouse_print_packet(get_mouse_packet());
              counter= 0;
            }
          }
          break;
        default:
          break;
      }
    }
  }

  if (mouse_write(DISABLE_DATA_REPORT) != 0) {
    timer_unsubscribe_int();
    mouse_unsubscribe_int();
    return 1;
  }

  if (timer_unsubscribe_int() != 0) {
    mouse_unsubscribe_int();
    return 1;
  }

  if (mouse_unsubscribe_int() != 0)
    return 1;

  return 0;
}
