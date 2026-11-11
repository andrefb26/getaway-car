#include <lcom/lcf.h>
#include <stdio.h>
#include <string.h>
#include "video_gr.h"

static uint8_t *video_mem = NULL;
static vbe_mode_info_t vmi;
static uint8_t bytes_per_pixel;

int vg_set_mode(uint16_t mode) {
    // Ask the BIOS to enter the VBE graphics mode using linear framebuffer.
    reg86_t reg;
    memset(&reg, 0, sizeof(reg));
    reg.intno = 0x10;
    reg.ax = 0x4F02;
    reg.bx = mode | BIT(14);
    if (sys_int86(&reg) != OK) return 1;
    if (reg.ax != 0x004F) return 1;
    return 0;
}

void *(vg_init)(uint16_t mode) {
    // Save the mode information first, because the drawing functions need it.
    if (vbe_get_mode_info(mode, &vmi) != 0) {
        printf("vg_init: failed to get mode info.\n");
        return NULL;
    }

    bytes_per_pixel = (vmi.BitsPerPixel + 7) / 8;
    unsigned int vram_size = (unsigned int) vmi.YResolution * vmi.BytesPerScanLine;
    phys_bytes vram_base = (phys_bytes) vmi.PhysBasePtr;

    // Allow this process to access the physical VRAM range.
    struct minix_mem_range mr;
    mr.mr_base = vram_base;
    mr.mr_limit = vram_base + vram_size;
    if (sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr) != OK) {
        printf("vg_init: failed to add VRAM memory permission.\n");
        return NULL;
    }

    // Map the physical video memory so the program can write pixels directly.
    video_mem = vm_map_phys(SELF, (void *) vram_base, vram_size);
    if (video_mem == MAP_FAILED || video_mem == NULL) {
        printf("vg_init: failed to map VRAM.\n");
        return NULL;
    }

    if (vg_set_mode(mode) != 0) {
        printf("vg_init: failed to set graphics mode.\n");
        return NULL;
    }

    return video_mem;
}

int vg_draw_pixel(uint16_t x, uint16_t y, uint32_t color) {
    // Do not draw outside the screen limits.
    if (x >= vmi.XResolution || y >= vmi.YResolution) return 1;

    // Calculate the pixel position in VRAM.
    uint32_t offset = ((uint32_t) y * vmi.XResolution + x) * bytes_per_pixel;

    // Copy only the bytes used by the current video mode.
    uint8_t *pixel = video_mem + offset;
    memcpy(pixel, &color, bytes_per_pixel);
    return 0;
}

int (vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color) {
    // If the whole line is below the screen, there is nothing to draw.
    if (y >= vmi.YResolution) return 0;

    // Draw only the part of the line that is inside the screen.
    for (uint16_t i = 0; i < len; i++) {
        // Use uint32_t to avoid overflow when x + i is bigger than uint16_t.
        uint32_t screen_x = (uint32_t) x + i;

        // Skip pixels that would be outside the right side of the screen.
        if (screen_x >= vmi.XResolution) continue;

        if (vg_draw_pixel((uint16_t) screen_x, y, color) != 0) return 1;
    }
    return 0;
}

int (vg_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color) {
    // A rectangle is drawn as several horizontal lines.
    for (uint16_t row = 0; row < height; row++) {
        // Use uint32_t to avoid overflow when y + row is too large.
        uint32_t screen_y = (uint32_t) y + row;

        // Skip rows that would be outside the bottom of the screen.
        if (screen_y >= vmi.YResolution) continue;

        // Draw the visible part of this row.
        if (vg_draw_hline(x, (uint16_t) screen_y, width, color) != 0) return 1;
    }
    return 0;
}

int vg_draw_pixmap(uint8_t *pixmap, xpm_image_t img, uint16_t x, uint16_t y) {
    if (pixmap == NULL) return 1;

    // Draw every pixel from the flat pixmap array.
    for (uint16_t row = 0; row < img.height; row++) {
        for (uint16_t col = 0; col < img.width; col++) {
            uint16_t screen_x = x + col;
            uint16_t screen_y = y + row;

            // Pixels outside the screen are ignored.
            if (screen_x >= vmi.XResolution || screen_y >= vmi.YResolution)
                continue;

            uint32_t color = pixmap[(uint32_t) row * img.width + col];
            if (vg_draw_pixel(screen_x, screen_y, color) != 0) return 1;
        }
    }
    return 0;
}


uint8_t *vg_get_video_mem(void) { return video_mem; }
uint16_t vg_get_x_res(void) { return vmi.XResolution; }
uint16_t vg_get_y_res(void) { return vmi.YResolution; }
uint8_t vg_get_bytes_per_pixel(void) { return bytes_per_pixel; }

int vg_draw_xpm_to_buffer(uint8_t *dest, uint16_t dest_width, uint16_t dest_height,
                          const uint8_t *pixmap, int pixmap_width, int pixmap_height,
                          int x, int y, uint8_t transparent_index) {
    if (!dest || !pixmap) return 1;
    for (int row = 0; row < pixmap_height; row++) {
        int screen_y = y + row;
        if (screen_y < 0 || screen_y >= dest_height) continue;
        for (int col = 0; col < pixmap_width; col++) {
            int screen_x = x + col;
            if (screen_x < 0 || screen_x >= dest_width) continue;
            uint8_t color = pixmap[(uint32_t) row * pixmap_width + col];
            if (color == transparent_index) continue;
            dest[(uint32_t) screen_y * dest_width + screen_x] = color;
        }
    }
    return 0;
}
