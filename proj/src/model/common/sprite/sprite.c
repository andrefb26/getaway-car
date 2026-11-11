#include "sprite.h"
#include "../../../controller/palette/palette.h"
#include <lcom/lcf.h>
#include <stdlib.h>

Sprite* create_sprite(xpm_map_t map) {
    Sprite *sp = malloc(sizeof(Sprite));
    if (!sp) return NULL;

    xpm_image_t img;
    uint8_t *raw = xpm_load(map, XPM_8_8_8_8, &img);
    if (!raw) { free(sp); return NULL; }

    int n = img.width * img.height;
    sp->pixmap = malloc(n);
    if (!sp->pixmap) { free(raw); free(sp); return NULL; }

    uint32_t *argb = (uint32_t *)raw;
    for (int i = 0; i < n; i++) {
        uint32_t px = argb[i];
        uint8_t r = (px >> 16) & 0xFF;
        uint8_t g = (px >> 8)  & 0xFF;
        uint8_t b =  px        & 0xFF;
        sp->pixmap[i] = (r == 0xFF && g == 0x00 && b == 0xFF)
                      ? PAL_TRANSPARENT : palette_find_index(r, g, b);
    }

    free(raw);
    sp->width  = img.width;
    sp->height = img.height;
    return sp;
}

void sprite_destroy(Sprite *sp) {
    if (!sp) return;
    free(sp->pixmap);
    free(sp);
}
