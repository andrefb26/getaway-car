#include "menu_view.h"
#include "../../view.h"
#include "../../../model/resources/resources.h"
#include "../../../controller/input/input.h"
#include "config.h"

#define MENU_START        0
#define MENU_INSTRUCTIONS 1
#define MENU_LEADERBOARD  2
#define MENU_EXIT         3

#define BTN_Y_START        310
#define BTN_Y_INSTRUCTIONS 400
#define BTN_Y_LEADERBOARD  490
#define BTN_Y_EXIT         580

void menu_view_draw(int selection) {
    Sprite *title            = resources_get_menu_title();
    Sprite *start_btn        = resources_get_menu_start_btn();
    Sprite *instructions_btn = resources_get_menu_instructions_btn();
    Sprite *leaderboard_btn  = resources_get_menu_leaderboard_btn();
    Sprite *exit_btn         = resources_get_menu_exit_btn();

    if (title) {
        int tw = title->width  * 3 / 2;
        int th = title->height * 3 / 2;
        draw_sprite_scaled(title, (SCREEN_W - tw) / 2, 130, tw, th);
    }

    /* Draw each button: scale up slightly when selected. */
    if (start_btn) {
        int bw = start_btn->width  * 5 / 4;
        int bh = start_btn->height * 5 / 4;
        if (selection == MENU_START) {
            int w = bw * 9 / 8, h = bh * 9 / 8;
            draw_sprite_scaled(start_btn, (SCREEN_W - w) / 2, BTN_Y_START - (h - bh) / 2, w, h);
        } else {
            draw_sprite_scaled(start_btn, (SCREEN_W - bw) / 2, BTN_Y_START, bw, bh);
        }
    }

    if (instructions_btn) {
        int bw = instructions_btn->width  * 5 / 4;
        int bh = instructions_btn->height * 5 / 4;
        if (selection == MENU_INSTRUCTIONS) {
            int w = bw * 9 / 8, h = bh * 9 / 8;
            draw_sprite_scaled(instructions_btn, (SCREEN_W - w) / 2, BTN_Y_INSTRUCTIONS - (h - bh) / 2, w, h);
        } else {
            draw_sprite_scaled(instructions_btn, (SCREEN_W - bw) / 2, BTN_Y_INSTRUCTIONS, bw, bh);
        }
    }

    if (leaderboard_btn) {
        int bw = leaderboard_btn->width  * 5 / 4;
        int bh = leaderboard_btn->height * 5 / 4;
        if (selection == MENU_LEADERBOARD) {
            int w = bw * 9 / 8, h = bh * 9 / 8;
            draw_sprite_scaled(leaderboard_btn, (SCREEN_W - w) / 2, BTN_Y_LEADERBOARD - (h - bh) / 2, w, h);
        } else {
            draw_sprite_scaled(leaderboard_btn, (SCREEN_W - bw) / 2, BTN_Y_LEADERBOARD, bw, bh);
        }
    }

    if (exit_btn) {
        int bw = exit_btn->width  * 5 / 4;
        int bh = exit_btn->height * 5 / 4;
        if (selection == MENU_EXIT) {
            int w = bw * 9 / 8, h = bh * 9 / 8;
            draw_sprite_scaled(exit_btn, (SCREEN_W - w) / 2, BTN_Y_EXIT - (h - bh) / 2, w, h);
        } else {
            draw_sprite_scaled(exit_btn, (SCREEN_W - bw) / 2, BTN_Y_EXIT, bw, bh);
        }
    }

    draw_sprite(resources_get_cursor_sprite(), input_cursor_x(), input_cursor_y());
}
