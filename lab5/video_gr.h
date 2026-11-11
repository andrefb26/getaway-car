#pragma once

#include <stdint.h>
#include <lcom/vbe.h>
#include <lcom/xpm.h>

int vg_set_mode(uint16_t mode);
void *(vg_init)(uint16_t mode);
int vg_draw_pixel(uint16_t x, uint16_t y, uint32_t color);
int (vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color);
int (vg_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color);
int vg_draw_pixmap(uint8_t *pixmap, xpm_image_t img, uint16_t x, uint16_t y);
uint8_t* vg_get_video_mem(void);
uint16_t vg_get_x_res(void);
uint16_t vg_get_y_res(void);
uint8_t  vg_get_bytes_per_pixel(void);

int vg_draw_xpm_to_buffer(uint8_t *dest, uint16_t dest_width, uint16_t dest_height,
                          const uint8_t *pixmap, int pixmap_width, int pixmap_height,
                          int x, int y, uint8_t transparent_index);

