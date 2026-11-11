#include "mouse.h"

static int hook_id_mouse = 3;
static struct packet mouse_packet;
static uint8_t byte_index = 0;
static uint8_t mouse_bytes[3];
static uint8_t current_byte;
static bool packet_complete = false;

int (mouse_subscribe_int)(uint8_t *bit_no){
  if (bit_no == NULL) return 1;
  *bit_no = (hook_id_mouse);
  return sys_irqsetpolicy(IRQ_MOUSE, IRQ_REENABLE | IRQ_EXCLUSIVE, &hook_id_mouse);
}

int (mouse_unsubscribe_int)(){
  return sys_irqrmpolicy(&hook_id_mouse);
}

void (mouse_ih)() {
  if (kbc_read_outbuf(&current_byte, true) != 0)
    return;
  mouse_sync_bytes();
}

void (mouse_sync_bytes)() {
  if (byte_index == 0 && !(current_byte & BIT(3))) {
    return;
  }

  mouse_bytes[byte_index] = current_byte;
  byte_index++;

  if (byte_index == 3) {
    byte_index = 0;
    packet_complete = true;
  }
}

void (mouse_bytes_to_packet)() {
  mouse_packet.bytes[0] = mouse_bytes[0];
  mouse_packet.bytes[1] = mouse_bytes[1];
  mouse_packet.bytes[2] = mouse_bytes[2];

  mouse_packet.lb = mouse_bytes[0] & BIT(0);
  mouse_packet.rb = mouse_bytes[0] & BIT(1);
  mouse_packet.mb = mouse_bytes[0] & BIT(2);

  mouse_packet.x_ov = mouse_bytes[0] & BIT(6);
  mouse_packet.y_ov = mouse_bytes[0] & BIT(7);

  if (mouse_bytes[0] & BIT(4))
    mouse_packet.delta_x = (int16_t)(0xFF00 | mouse_bytes[1]);
  else
    mouse_packet.delta_x = mouse_bytes[1];

  if (mouse_bytes[0] & BIT(5))
    mouse_packet.delta_y = (int16_t)(0xFF00 | mouse_bytes[2]);
  else
    mouse_packet.delta_y = mouse_bytes[2];

  packet_complete = false;
}

bool (mouse_packet_ready)() {
  return packet_complete;
}

struct packet* (get_mouse_packet)() {
  return &mouse_packet;
}

int (mouse_write)(uint8_t command) {
  uint8_t response;

  for (int attempt = 0; attempt < KBC_MAX_TRIES; attempt++) {
    if (kbc_write_cmd(KBC_CMD_REG, WRITE_BYTE_MOUSE) != 0) continue;
    if (kbc_write_cmd(KBC_INBUF_REG, command) != 0)        continue;
    if (kbc_read_outbuf(&response, true) != 0)              continue;
    if (response == ACK) return 0;
    if (response == NACK || response == ERROR) continue;
  }

  return 1;
}
