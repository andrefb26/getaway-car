#include "view.h"
#include "video_gr.h"
#include "../controller/palette/palette.h"
#include <stdlib.h>
#include <string.h>

static uint8_t *back_buffer = NULL;

void view_init_buffers(void) {
    uint16_t w = vg_get_x_res();
    uint16_t h = vg_get_y_res();
    back_buffer = (uint8_t *) malloc((uint32_t)w * h);
}

void draw_sprite(Sprite *sp, int x, int y) {
    if (!sp || !sp->pixmap) return;
    vg_draw_xpm_to_buffer(back_buffer, vg_get_x_res(), vg_get_y_res(),
                          sp->pixmap, sp->width, sp->height,
                          x, y, PAL_TRANSPARENT);
}

void draw_sprite_scaled(Sprite *sp, int x, int y, int w, int h) {
    if (!sp || !sp->pixmap) return;
    int src_w = sp->width, src_h = sp->height;
    int scr_w = vg_get_x_res(), scr_h = vg_get_y_res();
    for (int row = 0; row < h; row++) {
        int sy = row * src_h / h;
        for (int col = 0; col < w; col++) {
            uint8_t c = sp->pixmap[sy * src_w + col * src_w / w];
            if (c == PAL_TRANSPARENT) continue;
            int px = x + col, py = y + row;
            if (px >= 0 && px < scr_w && py >= 0 && py < scr_h)
                back_buffer[py * scr_w + px] = c;
        }
    }
}

void draw_rect(int x, int y, int w, int h, uint8_t color) {
    int scr_w = vg_get_x_res(), scr_h = vg_get_y_res();
    for (int row = 0; row < h; row++) {
        int py = y + row;
        if (py < 0 || py >= scr_h) continue;
        for (int col = 0; col < w; col++) {
            int px = x + col;
            if (px >= 0 && px < scr_w)
                back_buffer[py * scr_w + px] = color;
        }
    }
}

void draw_clear(uint8_t color_index) {
    uint32_t size = (uint32_t)vg_get_x_res() * vg_get_y_res();
    memset(back_buffer, color_index, size);
}

void copy_buffer_to_video(void) {
    uint32_t size = (uint32_t)vg_get_x_res() * vg_get_y_res();
    memcpy(vg_get_video_mem(), back_buffer, size);
}
