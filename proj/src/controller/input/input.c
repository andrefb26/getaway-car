#include "input.h"
#include "kbc.h"
#include "../cursor/cursor.h"
#include "../../view/screens/biome_select/biome_select_view.h"
#include "../../view/screens/car_select/car_select_view.h"
#include "config.h"
#include <stdbool.h>
#include <stdlib.h>

#define ESC_MAKECODE        0x01
#define ENTER_MAKECODE      0x1C
#define ARROW_PREFIX        0xE0
#define ARROW_LEFT_CODE     0x4B
#define ARROW_RIGHT_CODE    0x4D
#define ARROW_UP_CODE       0x48
#define ARROW_DOWN_CODE     0x50
#define KEY_A_CODE          0x1E
#define KEY_D_CODE          0x20

/* Menu button layout */
/* Buttons are 256x64 XPMs drawn at 5/4 scale = 320x80 on screen */
#define MENU_BTN_W         320
#define MENU_BTN_H          80
#define MENU_START_X       ((SCREEN_W - MENU_BTN_W) / 2)
#define MENU_START_Y        310
#define MENU_INSTRUCTIONS_X ((SCREEN_W - MENU_BTN_W) / 2)
#define MENU_INSTRUCTIONS_Y  400
#define MENU_LEADERBOARD_X ((SCREEN_W - MENU_BTN_W) / 2)
#define MENU_LEADERBOARD_Y  490
#define MENU_EXIT_X        ((SCREEN_W - MENU_BTN_W) / 2)
#define MENU_EXIT_Y         580

/* Mode select card layout */
#define MODE_CARD_W   200
#define MODE_CARD_H   200
#define MODE_CARD_GAP  80
#define MODE_RACE_X  ((SCREEN_W - MODE_CARD_W * 2 - MODE_CARD_GAP) / 2)
#define MODE_ENDUR_X (MODE_RACE_X + MODE_CARD_W + MODE_CARD_GAP)
#define MODE_CARDS_Y  280

/* Pause button layout — must match pause_view.h */
#define PAUSE_BTN_X_C   412
#define PAUSE_BTN_W_C   200
#define PAUSE_BTN_H_C    44
#define PAUSE_RESUME_Y_C 356
#define PAUSE_QUIT_Y_C   414

/* Win screen button layout — must match win_view.h */
#define WIN_BTN_W_C      256
#define WIN_BTN_H_C       64
#define WIN_BTN_Y_C       580
#define WIN_PLAY_X_C      224
#define WIN_MENU_X_C      544

static bool     prev_extended  = false;
static bool     scancode_ready = false;
static Cursor  *menu_cursor    = NULL;
static bool     mouse_lb_event = false;
static bool     mouse_rb_event = false;
static int      inverted_car1  = 0;  /* >0 => A<->D invertidos */
static int      inverted_car2  = 0;  /* >0 => LMB<->RMB invertidos */

void input_init_cursor(int screen_w, int screen_h) {
    if (menu_cursor) destroy_cursor(menu_cursor);
    menu_cursor = create_cursor(screen_w / 2, screen_h / 2, screen_w, screen_h);
}

void input_mouse_update(int dx, int dy, bool lb, bool rb) {
    if (!menu_cursor) return;
    cursor_update(menu_cursor, dx, dy, lb, rb);
    if (cursor_left_clicked(menu_cursor))  mouse_lb_event = true;
    if (cursor_right_clicked(menu_cursor)) mouse_rb_event = true;
}

/* When inverted, swap LMB and RMB for car2 (controlled by mouse). */
int input_mouse_car2_left(void)  { return inverted_car2 > 0 ? mouse_rb_event : mouse_lb_event; }
int input_mouse_car2_right(void) { return inverted_car2 > 0 ? mouse_lb_event : mouse_rb_event; }

void input_set_car1_inverted(int ticks) { inverted_car1 = ticks; }
void input_set_car2_inverted(int ticks) { inverted_car2 = ticks; }
int  input_get_car1_inverted_ticks(void) { return inverted_car1; }
int  input_get_car2_inverted_ticks(void) { return inverted_car2; }
void input_tick_inverted(void) {
    if (inverted_car1 > 0) inverted_car1--;
    if (inverted_car2 > 0) inverted_car2--;
}

void input_update(void) {
    uint8_t sc = get_current_scancode();
    if (sc == ARROW_PREFIX) {
        prev_extended  = true;
        scancode_ready = false; /* prefix byte — wait for the actual key code */
    } else {
        scancode_ready = true;
    }
}

void input_flush(void) {
    scancode_ready = false;
    prev_extended  = false;
    mouse_lb_event = false;
    mouse_rb_event = false;
    if (menu_cursor) menu_cursor->clicked = false;
}

int input_esc_pressed(void) {
    return scancode_ready && get_current_scancode() == ESC_MAKECODE;
}

int input_keyboard_start_pressed(void)   { return scancode_ready && get_current_scancode() == ENTER_MAKECODE; }
int input_keyboard_restart_pressed(void) { return scancode_ready && get_current_scancode() == ENTER_MAKECODE; }
int input_keyboard_menu_pressed(void)    { return scancode_ready && get_current_scancode() == ESC_MAKECODE; }

int input_keyboard_car_left_pressed(void) {
    return scancode_ready && prev_extended && get_current_scancode() == ARROW_LEFT_CODE;
}

int input_keyboard_car_right_pressed(void) {
    return scancode_ready && prev_extended && get_current_scancode() == ARROW_RIGHT_CODE;
}

/* When inverted, A moves right and D moves left for car1. */
int input_keyboard_car1_left_pressed(void)  {
    if (!scancode_ready) return 0;
    uint8_t sc = get_current_scancode();
    return inverted_car1 > 0 ? (sc == KEY_D_CODE) : (sc == KEY_A_CODE);
}
int input_keyboard_car1_right_pressed(void) {
    if (!scancode_ready) return 0;
    uint8_t sc = get_current_scancode();
    return inverted_car1 > 0 ? (sc == KEY_A_CODE) : (sc == KEY_D_CODE);
}

int input_keyboard_pause_pressed(void)   { return scancode_ready && get_current_scancode() == ESC_MAKECODE; }
int input_keyboard_up_pressed(void)      { return scancode_ready && prev_extended && get_current_scancode() == ARROW_UP_CODE; }
int input_keyboard_down_pressed(void)    { return scancode_ready && prev_extended && get_current_scancode() == ARROW_DOWN_CODE; }
int input_keyboard_confirm_pressed(void) { return scancode_ready && get_current_scancode() == ENTER_MAKECODE; }

int input_menu_nav_up(void)    { return scancode_ready && prev_extended && get_current_scancode() == ARROW_UP_CODE; }
int input_menu_nav_down(void)  { return scancode_ready && prev_extended && get_current_scancode() == ARROW_DOWN_CODE; }
int input_menu_nav_left(void)  { return scancode_ready && prev_extended && get_current_scancode() == ARROW_LEFT_CODE; }
int input_menu_nav_right(void) { return scancode_ready && prev_extended && get_current_scancode() == ARROW_RIGHT_CODE; }

int input_mode_nav_left(void)  { return scancode_ready && prev_extended && get_current_scancode() == ARROW_LEFT_CODE; }
int input_mode_nav_right(void) { return scancode_ready && prev_extended && get_current_scancode() == ARROW_RIGHT_CODE; }

static int over_rect(int rx, int ry, int rw, int rh) {
    if (!menu_cursor) return 0;
    int cx = cursor_get_x(menu_cursor), cy = cursor_get_y(menu_cursor);
    return cx >= rx && cx < rx + rw && cy >= ry && cy < ry + rh;
}

int input_mouse_over_start(void)        { return over_rect(MENU_START_X,        MENU_START_Y,        MENU_BTN_W, MENU_BTN_H); }
int input_mouse_over_instructions(void) { return over_rect(MENU_INSTRUCTIONS_X, MENU_INSTRUCTIONS_Y, MENU_BTN_W, MENU_BTN_H); }
int input_mouse_over_leaderboard(void)  { return over_rect(MENU_LEADERBOARD_X,  MENU_LEADERBOARD_Y,  MENU_BTN_W, MENU_BTN_H); }
int input_mouse_over_exit(void)         { return over_rect(MENU_EXIT_X,         MENU_EXIT_Y,         MENU_BTN_W, MENU_BTN_H); }

int input_mouse_start_pressed(void) {
    return menu_cursor && cursor_left_clicked(menu_cursor) && input_mouse_over_start();
}
int input_mouse_instructions_pressed(void) {
    return menu_cursor && cursor_left_clicked(menu_cursor) && input_mouse_over_instructions();
}
int input_mouse_leaderboard_pressed(void) {
    return menu_cursor && cursor_left_clicked(menu_cursor) && input_mouse_over_leaderboard();
}
int input_mouse_exit_pressed(void) {
    return menu_cursor && cursor_left_clicked(menu_cursor) && input_mouse_over_exit();
}
int input_leaderboard_back_pressed(void) {
    return scancode_ready && get_current_scancode() == ESC_MAKECODE;
}
int input_mouse_restart_pressed(void) { return 0; }
int input_mouse_menu_pressed(void)    { return 0; }

int input_menu_start_pressed(void) {
    return input_keyboard_start_pressed() || input_mouse_start_pressed();
}

int input_gameover_restart_pressed(void) {
    return input_keyboard_restart_pressed() || input_mouse_restart_pressed();
}

int input_gameover_menu_pressed(void) {
    return input_keyboard_menu_pressed() || input_mouse_menu_pressed();
}

int input_mouse_over_race_card(void)        { return over_rect(MODE_RACE_X,  MODE_CARDS_Y, MODE_CARD_W, MODE_CARD_H); }
int input_mouse_over_endurance_card(void)   { return over_rect(MODE_ENDUR_X, MODE_CARDS_Y, MODE_CARD_W, MODE_CARD_H); }
int input_mouse_race_card_pressed(void)     { return menu_cursor && cursor_left_clicked(menu_cursor) && input_mouse_over_race_card(); }
int input_mouse_endurance_card_pressed(void){ return menu_cursor && cursor_left_clicked(menu_cursor) && input_mouse_over_endurance_card(); }

int input_mouse_over_pause_resume(void) {
    return over_rect(PAUSE_BTN_X_C, PAUSE_RESUME_Y_C, PAUSE_BTN_W_C, PAUSE_BTN_H_C);
}
int input_mouse_over_pause_quit(void) {
    return over_rect(PAUSE_BTN_X_C, PAUSE_QUIT_Y_C, PAUSE_BTN_W_C, PAUSE_BTN_H_C);
}
int input_mouse_pause_resume_pressed(void) {
    return menu_cursor && cursor_left_clicked(menu_cursor) && input_mouse_over_pause_resume();
}
int input_mouse_pause_quit_pressed(void) {
    return menu_cursor && cursor_left_clicked(menu_cursor) && input_mouse_over_pause_quit();
}
int input_mouse_over_win_play_again(void) {
    return over_rect(WIN_PLAY_X_C, WIN_BTN_Y_C, WIN_BTN_W_C, WIN_BTN_H_C);
}
int input_mouse_over_win_menu(void) {
    return over_rect(WIN_MENU_X_C, WIN_BTN_Y_C, WIN_BTN_W_C, WIN_BTN_H_C);
}
int input_mouse_win_play_again_pressed(void) {
    return menu_cursor && cursor_left_clicked(menu_cursor) && input_mouse_over_win_play_again();
}
int input_mouse_win_menu_pressed(void) {
    return menu_cursor && cursor_left_clicked(menu_cursor) && input_mouse_over_win_menu();
}
int input_cursor_x(void) { return menu_cursor ? cursor_get_x(menu_cursor) : 0; }
int input_cursor_y(void) { return menu_cursor ? cursor_get_y(menu_cursor) : 0; }

int input_biome_nav_left(void) {
    return (scancode_ready && !prev_extended && get_current_scancode() == KEY_A_CODE)
        || (scancode_ready && prev_extended  && get_current_scancode() == ARROW_LEFT_CODE);
}
int input_biome_nav_right(void) {
    return (scancode_ready && !prev_extended && get_current_scancode() == KEY_D_CODE)
        || (scancode_ready && prev_extended  && get_current_scancode() == ARROW_RIGHT_CODE);
}
int input_biome_select_pressed(void) { return scancode_ready && get_current_scancode() == ENTER_MAKECODE; }
int input_mouse_over_biome_select(void) {
    return over_rect(BIOME_SELECT_BTN_X, BIOME_SELECT_BTN_Y, BIOME_SELECT_BTN_W, BIOME_SELECT_BTN_H);
}
int input_mouse_biome_select_pressed(void) {
    return menu_cursor && cursor_left_clicked(menu_cursor) && input_mouse_over_biome_select();
}
int input_mouse_biome_arrow_left(void) {
    return menu_cursor && cursor_left_clicked(menu_cursor)
        && over_rect(BIOME_LARROW_X, BIOME_ARROW_Y, BIOME_ARROW_HIT, BIOME_ARROW_HIT);
}
int input_mouse_biome_arrow_right(void) {
    return menu_cursor && cursor_left_clicked(menu_cursor)
        && over_rect(BIOME_RARROW_X, BIOME_ARROW_Y, BIOME_ARROW_HIT, BIOME_ARROW_HIT);
}

int input_p1_nav_left(void)  { return scancode_ready && !prev_extended && get_current_scancode() == KEY_A_CODE; }
int input_p1_nav_right(void) { return scancode_ready && !prev_extended && get_current_scancode() == KEY_D_CODE; }
int input_p2_nav_left(void)  { return scancode_ready && prev_extended  && get_current_scancode() == ARROW_LEFT_CODE; }
int input_p2_nav_right(void) { return scancode_ready && prev_extended  && get_current_scancode() == ARROW_RIGHT_CODE; }
int input_car_select_race_pressed(void) { return scancode_ready && get_current_scancode() == ENTER_MAKECODE; }
int input_mouse_over_car_select_race_btn(void) {
    return over_rect(CAR_SELECT_RACE_BTN_X, CAR_SELECT_RACE_BTN_Y,
                     CAR_SELECT_RACE_BTN_W, CAR_SELECT_RACE_BTN_H);
}
int input_mouse_car_select_race_pressed(void) {
    return menu_cursor && cursor_left_clicked(menu_cursor)
           && input_mouse_over_car_select_race_btn();
}
