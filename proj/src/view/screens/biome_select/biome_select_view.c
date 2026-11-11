#include "biome_select_view.h"
#include "../../view.h"
#include "../../../model/resources/resources.h"
#include "../../../controller/input/input.h"
#include "../../../controller/palette/palette.h"
#include "../../../view/hud/timer/timer_view.h"
#include "config.h"

static uint8_t biome_bg_color(TrackTheme theme) {
    switch (theme) {
        case TRACK_THEME_DESERT: return PAL_GRASS_DRY;
        case TRACK_THEME_FOREST: return PAL_TTL_PINK;
        default:                 return PAL_GRASS_BASE;
    }
}
#define CARD_W          300
#define CARD_H          300
#define CARD_X         ((SCREEN_W - CARD_W) / 2)
#define CARD_Y          260
#define BORDER_T          4
#define ARROW_SIZE       40
#define ARROW_Y         (CARD_Y + (CARD_H - ARROW_SIZE) / 2)
#define LABEL_Y         (CARD_Y + CARD_H + 16)
#define COUNTER_Y       (LABEL_Y + 36)

/* Copied from car_select_view.c — static helpers not exported */
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

/* Copied from car_select_view.c */
static void draw_counter(int cx, int y, int current, int total) {
    Sprite *d_cur = resources_get_digit_sprite(current + 1);
    Sprite *colon  = resources_get_colon_sprite();
    Sprite *d_tot  = resources_get_digit_sprite(total);
    int dw = 32;
    if (d_cur) draw_sprite(d_cur, cx - dw - 4, y);
    if (colon)  draw_sprite(colon,  cx - colon->width / 2, y);
    if (d_tot)  draw_sprite(d_tot,  cx + dw - 8, y);
}

/* Copied from mode_select_view.c */
static void draw_card_highlight(int x, int y, int w, int h) {
    draw_rect(x - BORDER_T, y - BORDER_T, w + 2 * BORDER_T, BORDER_T, PAL_BTN_YLW);
    draw_rect(x - BORDER_T, y + h,        w + 2 * BORDER_T, BORDER_T, PAL_BTN_YLW);
    draw_rect(x - BORDER_T, y,            BORDER_T,          h,        PAL_BTN_YLW);
    draw_rect(x + w,        y,            BORDER_T,          h,        PAL_BTN_YLW);
}

void biome_select_view_draw(TrackTheme selected) {
    draw_rect(0, HUD_BAR_H, SCREEN_W, SCREEN_H - HUD_BAR_H, PAL_MENU_DARK);

    /* Title — NULL-safe: shows nothing until biome_select_title.xpm is created */
    Sprite *title = resources_get_biome_select_title();
    if (title) {
        int tw = title->width  * 3 / 2;
        int th = title->height * 3 / 2;
        draw_sprite_scaled(title, (SCREEN_W - tw) / 2, 130, tw, th);
    }

    /* Card preview: ground colour fills the card, road stripe in the centre.
     * Mirrors the actual in-game view (grass/sand/petals on sides, road in middle). */
    draw_rect(CARD_X, CARD_Y, CARD_W, CARD_H, biome_bg_color(selected));
    draw_card_highlight(CARD_X, CARD_Y, CARD_W, CARD_H);
    Sprite *preview = resources_get_tile_sprite_themed(0, selected);
    if (preview) {
        int road_w = CARD_W * 625 / 1000;  /* road ≈ 62.5 % of screen width */
        int road_x = CARD_X + (CARD_W - road_w) / 2;
        draw_sprite_scaled(preview, road_x, CARD_Y, road_w, CARD_H);
    }

    /* Navigation arrows */
    draw_arrow_left (BIOME_LARROW_X, ARROW_Y, ARROW_SIZE, PAL_BTN_YLW);
    draw_arrow_right(BIOME_RARROW_X, ARROW_Y, ARROW_SIZE, PAL_BTN_YLW);

    /* Biome name label — NULL-safe: fallback coloured rect until XPMs are created */
    Sprite *label = resources_get_biome_label(selected);
    if (label) {
        draw_sprite_scaled(label, (SCREEN_W - label->width) / 2, LABEL_Y,
                           label->width, label->height);
    } else {
        draw_rect((SCREEN_W - 128) / 2, LABEL_Y, 128, 24, PAL_BTN_YLW);
    }

    /* Counter "X / TRACK_THEME_COUNT" */
    draw_counter(SCREEN_W / 2, COUNTER_Y, (int)selected, TRACK_THEME_COUNT);

    /* SELECT button — reuses start_button.xpm, scales up on hover */
    Sprite *btn = resources_get_menu_start_btn();
    if (btn) {
        int hovered = input_mouse_over_biome_select();
        int w = hovered ? BIOME_SELECT_BTN_W * 9 / 8 : BIOME_SELECT_BTN_W;
        int h = hovered ? BIOME_SELECT_BTN_H * 9 / 8 : BIOME_SELECT_BTN_H;
        draw_sprite_scaled(btn,
            BIOME_SELECT_BTN_X - (w - BIOME_SELECT_BTN_W) / 2,
            BIOME_SELECT_BTN_Y - (h - BIOME_SELECT_BTN_H) / 2,
            w, h);
    }

    draw_sprite(resources_get_cursor_sprite(), input_cursor_x(), input_cursor_y());
}
