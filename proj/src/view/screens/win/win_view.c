#include "win_view.h"
#include "../../view.h"
#include "../../../model/resources/resources.h"
#include "../../../controller/input/input.h"
#include "../../../controller/palette/palette.h"

static void draw_btn_highlight(int x, int y, int w, int h) {
    draw_rect(x - WIN_BORDER_T, y - WIN_BORDER_T, w + 2 * WIN_BORDER_T, WIN_BORDER_T, PAL_BTN_YLW);
    draw_rect(x - WIN_BORDER_T, y + h,             w + 2 * WIN_BORDER_T, WIN_BORDER_T, PAL_BTN_YLW);
    draw_rect(x - WIN_BORDER_T, y,                 WIN_BORDER_T,          h,            PAL_BTN_YLW);
    draw_rect(x + w,            y,                 WIN_BORDER_T,          h,            PAL_BTN_YLW);
}

void win_view_draw(int winner, int selected) {
    Sprite *play_btn = resources_get_win_play_again_btn();
    Sprite *menu_btn = resources_get_win_menu_btn();

    if (winner == 0) {
        Sprite *blue = resources_get_win_img(1);
        Sprite *red  = resources_get_win_img(2);
        if (blue) draw_sprite_scaled(blue, WIN_DRAW_X, WIN_DRAW_Y, WIN_DRAW_IMG_W, WIN_DRAW_IMG_H);
        if (red)  draw_sprite_scaled(red,  WIN_DRAW_X + WIN_DRAW_IMG_W + WIN_DRAW_GAP, WIN_DRAW_Y, WIN_DRAW_IMG_W, WIN_DRAW_IMG_H);
    } else {
        Sprite *img = resources_get_win_img(winner);
        if (img) draw_sprite_scaled(img, WIN_IMG_X, WIN_IMG_Y, WIN_IMG_W, WIN_IMG_H);
    }

    int sel_w = WIN_BTN_W * 9 / 8;
    int sel_h = WIN_BTN_H * 9 / 8;

    if (selected == 0) {
        if (menu_btn) draw_sprite(menu_btn, WIN_MENU_X, WIN_BTN_Y);
        if (play_btn) {
            int sx = WIN_PLAY_X - (sel_w - WIN_BTN_W) / 2;
            int sy = WIN_BTN_Y  - (sel_h - WIN_BTN_H) / 2;
            draw_sprite_scaled(play_btn, sx, sy, sel_w, sel_h);
            draw_btn_highlight(sx, sy, sel_w, sel_h);
        }
    } else {
        if (play_btn) draw_sprite(play_btn, WIN_PLAY_X, WIN_BTN_Y);
        if (menu_btn) {
            int sx = WIN_MENU_X - (sel_w - WIN_BTN_W) / 2;
            int sy = WIN_BTN_Y  - (sel_h - WIN_BTN_H) / 2;
            draw_sprite_scaled(menu_btn, sx, sy, sel_w, sel_h);
            draw_btn_highlight(sx, sy, sel_w, sel_h);
        }
    }

    draw_sprite(resources_get_cursor_sprite(), input_cursor_x(), input_cursor_y());
}
