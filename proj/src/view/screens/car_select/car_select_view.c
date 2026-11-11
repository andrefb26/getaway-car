#include "car_select_view.h"
#include "../../view.h"
#include "../../../model/resources/resources.h"
#include "../../../controller/input/input.h"
#include "../../../controller/palette/palette.h"
#include "../../../view/hud/timer/timer_view.h"

#include "config.h"
#define PREVIEW_W     150
#define PREVIEW_H     150
#define PREVIEW_Y     300
#define P1_PREVIEW_X  ((HALF_W - PREVIEW_W) / 2)
#define P2_PREVIEW_X  (HALF_W + (HALF_W - PREVIEW_W) / 2)
#define ARROW_SIZE     40
#define ARROW_GAP      20
#define ARROW_Y       (PREVIEW_Y + (PREVIEW_H - ARROW_SIZE) / 2)
#define P1_LARROW_X   (P1_PREVIEW_X - ARROW_GAP - ARROW_SIZE)
#define P1_RARROW_X   (P1_PREVIEW_X + PREVIEW_W + ARROW_GAP)
#define P2_LARROW_X   (P2_PREVIEW_X - ARROW_GAP - ARROW_SIZE)
#define P2_RARROW_X   (P2_PREVIEW_X + PREVIEW_W + ARROW_GAP)
#define COUNTER_Y     (PREVIEW_Y + PREVIEW_H + 20)
#define BORDER_T        4

static void draw_arrow_left(int x, int y, int size, uint8_t color) {
    int half = size / 2;
    for (int i = 0; i < size; i++) {
        int dist = (i < half) ? (half - 1 - i) : (i - half);
        int bw = half - dist;
        if (bw > 0) draw_rect(x, y + i, bw, 1, color);
    }
}

static void draw_arrow_right(int x, int y, int size, uint8_t color) {
    int half = size / 2;
    for (int i = 0; i < size; i++) {
        int dist = (i < half) ? (half - 1 - i) : (i - half);
        int bw = half - dist;
        if (bw > 0) draw_rect(x + size - bw, y + i, bw, 1, color);
    }
}

static void draw_preview_border(int x, int y, uint8_t color) {
    draw_rect(x - BORDER_T, y - BORDER_T, PREVIEW_W + 2 * BORDER_T, BORDER_T, color);
    draw_rect(x - BORDER_T, y + PREVIEW_H, PREVIEW_W + 2 * BORDER_T, BORDER_T, color);
    draw_rect(x - BORDER_T, y, BORDER_T, PREVIEW_H, color);
    draw_rect(x + PREVIEW_W, y, BORDER_T, PREVIEW_H, color);
}

static void draw_counter(int cx, int y, int current, int total) {
    Sprite *d_cur = resources_get_digit_sprite(current + 1);
    Sprite *colon  = resources_get_colon_sprite();
    Sprite *d_tot  = resources_get_digit_sprite(total);
    int dw = 32;
    if (d_cur) draw_sprite(d_cur, cx - dw - 4, y);
    if (colon)  draw_sprite(colon,  cx - colon->width / 2, y);
    if (d_tot)  draw_sprite(d_tot,  cx + dw - 8, y);
}

void car_select_view_draw(int p1_fmt, int p2_fmt, int fmt_count) {
    draw_rect(0,      HUD_BAR_H, HALF_W,  SCREEN_H - HUD_BAR_H, PAL_MENU_DARK);
    draw_rect(HALF_W, HUD_BAR_H, HALF_W,  SCREEN_H - HUD_BAR_H, PAL_MENU_DARK);
    draw_rect(HALF_W - 1, HUD_BAR_H, 2, SCREEN_H - HUD_BAR_H, PAL_GREY_MID);

    /* P1 label indicator */
    draw_rect(HALF_W / 2 - 20, HUD_BAR_H + 10, 40, 20, PAL_P1_INDICATOR);
    /* P2 label indicator */
    draw_rect(HALF_W + HALF_W / 2 - 20, HUD_BAR_H + 10, 40, 20, PAL_P2_INDICATOR);

    /* Car previews */
    Sprite *sp1 = resources_get_car_format_preview(p1_fmt, 0);
    Sprite *sp2 = resources_get_car_format_preview(p2_fmt, 1);
    if (sp1) draw_sprite_scaled(sp1, P1_PREVIEW_X, PREVIEW_Y, PREVIEW_W, PREVIEW_H);
    if (sp2) draw_sprite_scaled(sp2, P2_PREVIEW_X, PREVIEW_Y, PREVIEW_W, PREVIEW_H);

    /* Preview borders */
    draw_preview_border(P1_PREVIEW_X, PREVIEW_Y, PAL_P1_INDICATOR);
    draw_preview_border(P2_PREVIEW_X, PREVIEW_Y, PAL_P2_INDICATOR);

    /* Navigation arrows */
    draw_arrow_left (P1_LARROW_X, ARROW_Y, ARROW_SIZE, PAL_BTN_YLW);
    draw_arrow_right(P1_RARROW_X, ARROW_Y, ARROW_SIZE, PAL_BTN_YLW);
    draw_arrow_left (P2_LARROW_X, ARROW_Y, ARROW_SIZE, PAL_BTN_YLW);
    draw_arrow_right(P2_RARROW_X, ARROW_Y, ARROW_SIZE, PAL_BTN_YLW);

    /* Format counters */
    if (fmt_count > 0 && fmt_count <= 9) {
        int cx1 = P1_PREVIEW_X + PREVIEW_W / 2;
        int cx2 = P2_PREVIEW_X + PREVIEW_W / 2;
        draw_counter(cx1, COUNTER_Y, p1_fmt, fmt_count);
        draw_counter(cx2, COUNTER_Y, p2_fmt, fmt_count);
    }

    /* RACE button */
    Sprite *rbtn = resources_get_mode_race_label();
    int hovered  = input_mouse_over_car_select_race_btn();
    if (rbtn) {
        int w = hovered ? CAR_SELECT_RACE_BTN_W * 9 / 8 : CAR_SELECT_RACE_BTN_W;
        int h = hovered ? CAR_SELECT_RACE_BTN_H * 9 / 8 : CAR_SELECT_RACE_BTN_H;
        draw_sprite_scaled(rbtn,
            CAR_SELECT_RACE_BTN_X - (w - CAR_SELECT_RACE_BTN_W) / 2,
            CAR_SELECT_RACE_BTN_Y - (h - CAR_SELECT_RACE_BTN_H) / 2,
            w, h);
    } else {
        uint8_t bc = hovered ? PAL_BTN_YLW_LGT : PAL_BTN_YLW;
        draw_rect(CAR_SELECT_RACE_BTN_X, CAR_SELECT_RACE_BTN_Y, CAR_SELECT_RACE_BTN_W, CAR_SELECT_RACE_BTN_H, bc);
    }

    draw_sprite(resources_get_cursor_sprite(), input_cursor_x(), input_cursor_y());
}
