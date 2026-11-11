#include "timer_view.h"
#include "../../view.h"
#include "../../../model/resources/resources.h"
#include "../../../controller/palette/palette.h"

#include "config.h"
#define DIGIT_W      24
#define DIGIT_H      32
#define DIGIT_Y    ((HUD_BAR_H - DIGIT_H) / 2)
#define BORDER_H      2

void timer_view_draw(uint32_t elapsed_ticks) {
    draw_rect(0, 0, SCREEN_W, HUD_BAR_H, PAL_HUD_BG);
    draw_rect(0, HUD_BAR_H - BORDER_H, SCREEN_W, BORDER_H, PAL_HUD_BORDER);

    uint32_t total_secs = elapsed_ticks / TIMER_FREQ;
    uint32_t minutes    = total_secs / 60;
    uint32_t seconds    = total_secs % 60;

    /* MM:SS = 5 chars × DIGIT_W each, centered */
    int x = (SCREEN_W - 5 * DIGIT_W) / 2;

    draw_sprite_scaled(resources_get_digit_sprite((int)(minutes / 10)), x,              DIGIT_Y, DIGIT_W, DIGIT_H);
    draw_sprite_scaled(resources_get_digit_sprite((int)(minutes % 10)), x + DIGIT_W,    DIGIT_Y, DIGIT_W, DIGIT_H);
    draw_sprite_scaled(resources_get_colon_sprite(),                     x + 2 * DIGIT_W, DIGIT_Y, DIGIT_W, DIGIT_H);
    draw_sprite_scaled(resources_get_digit_sprite((int)(seconds / 10)), x + 3 * DIGIT_W, DIGIT_Y, DIGIT_W, DIGIT_H);
    draw_sprite_scaled(resources_get_digit_sprite((int)(seconds % 10)), x + 4 * DIGIT_W, DIGIT_Y, DIGIT_W, DIGIT_H);
}
