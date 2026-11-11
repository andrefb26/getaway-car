#include <lcom/lcf.h>

#include <lcom/lab5.h>

#include <stdint.h>
#include <stdio.h>

#include "video_gr.h"

// Values used to read the keyboard directly in the tests.
#define KBD_IRQ 1
#define KBC_OUT 0x60
#define BREAK_ESC 0x81

int main(int argc, char *argv[]) {
    // sets the language of LCF messages (can be either EN-US or PT-PT)
    lcf_set_language("EN-US");

    // enables to log function invocations that are being "wrapped" by LCF
    // [comment this out if you don't want/need it]
    lcf_trace_calls("/home/lcom/labs/lab5/trace.txt");

    // enables to save the output of printf function calls on a file
    // [comment this out if you don't want/need it]
    lcf_log_output("/home/lcom/labs/lab5/output.txt");

    // handles control over to LCF
    // [LCF handles command line arguments and invokes the right function]
    if (lcf_start(argc, argv))
        return 1;

    // LCF clean up tasks
    // [must be the last statement before return]
    lcf_cleanup();

    return 0;
}

static int wait_for_esc(void) {
    // This function waits until the user releases the ESC key.
    // It is used so the image/rectangle stays on the screen.
    int ipc_status;
    message msg;
    int kbd_hook_id = 5;
    uint8_t kbd_bit_no = kbd_hook_id;

    // Subscribe keyboard interrupts before entering the event loop.
    if (sys_irqsetpolicy(KBD_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &kbd_hook_id) != 0) {
        printf("Failed to subscribe keyboard interrupts.\n");
        return 1;
    }

    bool done = false;
    while (!done) {
        // Wait for a notification from the kernel.
        if (driver_receive(ANY, &msg, &ipc_status) != 0) continue;

        // Only hardware interrupts matter here.
        if (!is_ipc_notify(ipc_status)) continue;
        if (_ENDPOINT_P(msg.m_source) != HARDWARE) continue;

        if (msg.m_notify.interrupts & BIT(kbd_bit_no)) {
            // Read the scancode from the keyboard output buffer.
            uint32_t scancode;
            if (sys_inb(KBC_OUT, &scancode) != OK) continue;

            // ESC breakcode means the key was released, so the test can end.
            if ((uint8_t)scancode == BREAK_ESC)
                done = true;
        }
    }

    // Remove the keyboard interrupt subscription before leaving.
    return sys_irqrmpolicy(&kbd_hook_id);
}

int(video_test_init)(uint16_t mode, uint8_t delay) {
    // Enter the requested graphics mode.
    if (vg_init(mode) == NULL) return 1;

    // Keep the mode active for the number of seconds passed by LCF.
    tickdelay(micros_to_ticks((uint32_t)delay * 1000000));

    // Return to text mode.
    return vg_exit();
}

int(video_test_rectangle)(uint16_t mode, uint16_t x, uint16_t y,
                          uint16_t width, uint16_t height, uint32_t color) {
    // Enter the graphics mode requested by the test.
    if (vg_init(mode) == NULL) return 1;

    // Draw the rectangle with the given position, size and color.
    if (vg_draw_rectangle(x, y, width, height, color) != 0) {
        vg_exit();
        return 1;
    }

    // Leave the rectangle visible until ESC is released.
    if (wait_for_esc() != 0) {
        vg_exit();
        return 1;
    }

    return vg_exit();
}

int(video_test_xpm)(xpm_map_t xpm, uint16_t x, uint16_t y) {
    // The XPM test always uses mode 0x105, which is indexed 8 bpp.
    if (vg_init(0x105) == NULL) {
        printf("Failed to initialize video mode 0x105.\n");
        return 1;
    }

    // Decode the XPM selected by LCF into an image structure.
    xpm_image_t img;
    uint8_t *sprite = xpm_load(xpm, XPM_INDEXED, &img);
    if (sprite == NULL) {
        printf("Failed to load XPM.\n");
        vg_exit();
        return 1;
    }

    // Copy the pixels from the XPM image to VRAM.
    if (vg_draw_pixmap(sprite, img, x, y) != 0) {
        printf("Failed to draw XPM.\n");
        vg_exit();
        return 1;
    }

    // Keep the image on the screen until ESC is released.
    if (wait_for_esc() != 0) {
        vg_exit();
        return 1;
    }

    return vg_exit();
}
