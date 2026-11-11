#include "minimap_view.h"
#include "../../view.h"
#include "../../../controller/palette/palette.h"
#include "../timer/timer_view.h"

#define MAP_X       8
#define MAP_Y       (HUD_BAR_H + 6)
#define MAP_W       28
#define MAP_H       104
#define MAP_BORDER  1
#define STRIP_W     8
#define DOT_SIZE    4

void minimap_view_draw(const Car *car1, const Car *car2, const Track *track) {
    if (!track) return;

    /* Outer border */
    draw_rect(MAP_X, MAP_Y, MAP_W, MAP_H, PAL_HUD_BORDER);

    /* Inner background */
    int ix = MAP_X + MAP_BORDER;
    int iy = MAP_Y + MAP_BORDER;
    int iw = MAP_W - 2 * MAP_BORDER;
    int ih = MAP_H - 2 * MAP_BORDER;
    draw_rect(ix, iy, iw, ih, PAL_GREY_VERY_DARK);

    /* Track strip centred in inner area */
    int sx = ix + (iw - STRIP_W) / 2;
    draw_rect(sx, iy, STRIP_W, ih, PAL_ASPHALT_MID);

    /* 2-row checkered finish line at the top of the strip */
    draw_rect(sx,             iy,     STRIP_W / 2, 1, PAL_FINISH_DARK);
    draw_rect(sx + STRIP_W/2, iy,     STRIP_W / 2, 1, PAL_FINISH_LIGHT);
    draw_rect(sx,             iy + 1, STRIP_W / 2, 1, PAL_FINISH_LIGHT);
    draw_rect(sx + STRIP_W/2, iy + 1, STRIP_W / 2, 1, PAL_FINISH_DARK);

    /* Car dot positions: progress fraction 0=start(bottom) → 1=finish(top) */
    int base_row = track->scroll_row + CAR_SCREEN_ROW;
    int drawable = ih - DOT_SIZE;

    if (car1 && car1->base.is_active) {
        int row = base_row + car1->track_progress;
        if (row > TRACK_TOTAL_ROWS) row = TRACK_TOTAL_ROWS;
        float f = (float)row / (float)TRACK_TOTAL_ROWS;
        int dy = iy + (int)((1.0f - f) * (float)drawable);
        draw_rect(sx, dy, DOT_SIZE, DOT_SIZE, PAL_CAR1_NORMAL);
    }

    if (car2 && car2->base.is_active) {
        int row = base_row + car2->track_progress;
        if (row > TRACK_TOTAL_ROWS) row = TRACK_TOTAL_ROWS;
        float f = (float)row / (float)TRACK_TOTAL_ROWS;
        int dy = iy + (int)((1.0f - f) * (float)drawable);
        draw_rect(sx + DOT_SIZE, dy, DOT_SIZE, DOT_SIZE, PAL_CAR2_NORMAL);
    }
}
