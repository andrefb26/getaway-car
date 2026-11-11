#include "leaderboard_view.h"
#include "../../view.h"
#include "video_gr.h"
#include "../../../model/leaderboard/leaderboard.h"
#include "../../../model/common/sprite/sprite.h"
#include "../../../model/resources/resources.h"
#include "../../../controller/palette/palette.h"
#include <string.h>

/* ── XPM sources ──────────────────────────────────────────────────── */
#include "../../../assets/xpm/ui/screens/leaderboard/leaderboard.xpm"
#include "../../../assets/xpm/ui/screens/leaderboard/chars/char_A.xpm"
#include "../../../assets/xpm/ui/screens/leaderboard/chars/char_B.xpm"
#include "../../../assets/xpm/ui/screens/leaderboard/chars/char_D.xpm"
#include "../../../assets/xpm/ui/screens/leaderboard/chars/char_E.xpm"
#include "../../../assets/xpm/ui/screens/leaderboard/chars/char_I.xpm"
#include "../../../assets/xpm/ui/screens/leaderboard/chars/char_K.xpm"
#include "../../../assets/xpm/ui/screens/leaderboard/chars/char_L.xpm"
#include "../../../assets/xpm/ui/screens/leaderboard/chars/char_M.xpm"
#include "../../../assets/xpm/ui/screens/leaderboard/chars/char_N.xpm"
#include "../../../assets/xpm/ui/screens/leaderboard/chars/char_O.xpm"
#include "../../../assets/xpm/ui/screens/leaderboard/chars/char_P.xpm"
#include "../../../assets/xpm/ui/screens/leaderboard/chars/char_R.xpm"
#include "../../../assets/xpm/ui/screens/leaderboard/chars/char_T.xpm"
#include "../../../assets/xpm/ui/screens/leaderboard/chars/char_U.xpm"
#include "../../../assets/xpm/ui/screens/leaderboard/chars/char_W.xpm"
#include "../../../assets/xpm/ui/screens/leaderboard/chars/char_Y.xpm"

#define PANEL_W   700
#define PANEL_H   550
#define CHAR_W     24
#define CHAR_H     32
#define ROW_H      58
#define TEXT_V_OFF ((ROW_H - CHAR_H) / 2)

#define COL_RANK    20
#define COL_PLAYER 140
#define COL_TIME   300
#define COL_DATE   490

static const int row_y[7] = { 77, 124, 183, 242, 301, 360, 419 };

static Sprite *bg_sprite;
static Sprite *char_sprites[26]; /* char_sprites[i] => letter ('A' + i) */

void leaderboard_view_init(void) {
    bg_sprite = create_sprite((xpm_map_t)leaderboard_bg);

    memset(char_sprites, 0, sizeof(char_sprites));
    char_sprites['A' - 'A'] = create_sprite((xpm_map_t)char_A);
    char_sprites['B' - 'A'] = create_sprite((xpm_map_t)char_B);
    char_sprites['D' - 'A'] = create_sprite((xpm_map_t)char_D);
    char_sprites['E' - 'A'] = create_sprite((xpm_map_t)char_E);
    char_sprites['I' - 'A'] = create_sprite((xpm_map_t)char_I);
    char_sprites['K' - 'A'] = create_sprite((xpm_map_t)char_K);
    char_sprites['L' - 'A'] = create_sprite((xpm_map_t)char_L);
    char_sprites['M' - 'A'] = create_sprite((xpm_map_t)char_M);
    char_sprites['N' - 'A'] = create_sprite((xpm_map_t)char_N);
    char_sprites['O' - 'A'] = create_sprite((xpm_map_t)char_O);
    char_sprites['P' - 'A'] = create_sprite((xpm_map_t)char_P);
    char_sprites['R' - 'A'] = create_sprite((xpm_map_t)char_R);
    char_sprites['T' - 'A'] = create_sprite((xpm_map_t)char_T);
    char_sprites['U' - 'A'] = create_sprite((xpm_map_t)char_U);
    char_sprites['W' - 'A'] = create_sprite((xpm_map_t)char_W);
    char_sprites['Y' - 'A'] = create_sprite((xpm_map_t)char_Y);
}

static Sprite *get_char_sprite(char c) {
    if (c >= 'A' && c <= 'Z') return char_sprites[(int)(c - 'A')];
    if (c >= '0' && c <= '9') return resources_get_digit_sprite(c - '0');
    if (c == ':')              return resources_get_colon_sprite();
    return NULL;
}

static void draw_string(const char *str, int x, int y) {
    for (int i = 0; str[i] != '\0'; i++) {
        Sprite *sp = get_char_sprite(str[i]);
        if (sp) draw_sprite(sp, x + i * CHAR_W, y);
    }
}

static void draw_digits2(int val, int x, int y) {
    Sprite *d0 = resources_get_digit_sprite(val / 10);
    Sprite *d1 = resources_get_digit_sprite(val % 10);
    if (d0) draw_sprite(d0, x,          y);
    if (d1) draw_sprite(d1, x + CHAR_W, y);
}

/* ── small-digit helpers for the DATE column (15×20 px per glyph) ── */
#define SM_W  15
#define SM_H  20
#define SM_V_OFF ((ROW_H - SM_H) / 2)

static void draw_sm2(int val, int x, int y) {
    Sprite *d0 = resources_get_digit_sprite(val / 10);
    Sprite *d1 = resources_get_digit_sprite(val % 10);
    if (d0) draw_sprite_scaled(d0, x,        y, SM_W, SM_H);
    if (d1) draw_sprite_scaled(d1, x + SM_W, y, SM_W, SM_H);
}

static void draw_sm_colon(int x, int y) {
    Sprite *c = resources_get_colon_sprite();
    if (c) draw_sprite_scaled(c, x, y, SM_W, SM_H);
}

/* draws a small white forward-slash as a 2×(SM_H-4) rectangle */
static void draw_sm_slash(int x, int y) {
    draw_rect(x + SM_W / 2 - 1, y + 2, 2, SM_H - 4, PAL_WHITE);
}

void leaderboard_view_draw(void) {
    int sw = (int)vg_get_x_res();
    int sh = (int)vg_get_y_res();
    int px = (sw - PANEL_W) / 2;
    int py = (sh - PANEL_H) / 2;

    if (bg_sprite) draw_sprite(bg_sprite, px, py);

    /* "LEADERBOARD" centred in the title bar (0..row_y[0]) */
    {
        const char *title = "LEADERBOARD";
        int title_len = 11;
        int tx = px + (PANEL_W - title_len * CHAR_W) / 2;
        int ty = py + (row_y[0] - CHAR_H) / 2;
        draw_string(title, tx, ty);
    }

    int hy = py + row_y[0] + TEXT_V_OFF;
    draw_string("RANK",   px + COL_RANK,   hy);
    draw_string("PLAYER", px + COL_PLAYER, hy);
    draw_string("TIME",   px + COL_TIME,   hy);
    draw_string("DATE",   px + COL_DATE,   hy);

    Leaderboard *lb = leaderboard_get();
    for (int i = 0; i < lb->count && i < MAX_LEADERBOARD; i++) {
        LeaderboardEntry *e  = &lb->entries[i];
        int               ry = py + row_y[i + 1] + TEXT_V_OFF;

        Sprite *rank_sp = resources_get_digit_sprite(i + 1);
        if (rank_sp) draw_sprite(rank_sp, px + COL_RANK, ry);

        draw_string(e->player, px + COL_PLAYER, ry);

        int mins  = e->race_time_sec / 60;
        int secs  = e->race_time_sec % 60;
        int tx    = px + COL_TIME;
        Sprite *colon = resources_get_colon_sprite();
        draw_digits2(mins, tx, ry);              tx += 2 * CHAR_W;
        if (colon) draw_sprite(colon, tx, ry);  tx += CHAR_W;
        draw_digits2(secs, tx, ry);

        /* DATE: DD/MM HH:MM:SS in smaller (15×20) digits */
        int sm_y = py + row_y[i + 1] + SM_V_OFF;
        int dx   = px + COL_DATE;
        draw_sm2(e->rtc_day,   dx, sm_y); dx += 2 * SM_W;
        draw_sm_slash(dx, sm_y);          dx += SM_W;
        draw_sm2(e->rtc_month, dx, sm_y); dx += 2 * SM_W + 4;
        draw_sm2(e->rtc_hour,  dx, sm_y); dx += 2 * SM_W;
        draw_sm_colon(dx, sm_y);          dx += SM_W;
        draw_sm2(e->rtc_min,   dx, sm_y); dx += 2 * SM_W;
        draw_sm_colon(dx, sm_y);          dx += SM_W;
        draw_sm2(e->rtc_sec,   dx, sm_y);
    }
}
