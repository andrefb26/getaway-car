#include "heart_view.h"
#include "../../view.h"
#include "../../../model/resources/resources.h"
#include "../timer/timer_view.h"

#define HEART_SIZE   48
#define HEART_GAP     6
#define HUD_Y         8
#include "config.h"
#define ICON_SIZE    32
#define EFF_DIGIT_W  20
#define EFF_DIGIT_H  28
#define EFF_GAP       6

#define EFF_BLOCK_W  (ICON_SIZE + 4 + EFF_DIGIT_W)
#define EFF_ICON_Y   ((HUD_BAR_H - ICON_SIZE) / 2)
#define EFF_DIGIT_Y  ((HUD_BAR_H - EFF_DIGIT_H) / 2)

static void draw_effect(Sprite *icon, int ticks, int x) {
    if (!icon || ticks <= 0) return;
    draw_sprite_scaled(icon, x, EFF_ICON_Y, ICON_SIZE, ICON_SIZE);
    int secs = (ticks + 59) / 60;
    if (secs > 9) secs = 9;
    Sprite *d = resources_get_digit_sprite(secs);
    if (d) draw_sprite_scaled(d, x + ICON_SIZE + 4, EFF_DIGIT_Y, EFF_DIGIT_W, EFF_DIGIT_H);
}

void heart_view_draw(const Car *car1, const Car *car2, int banana_ticks1, int banana_ticks2) {
    Sprite *heart  = resources_get_heart_sprite();
    Sprite *banana = resources_get_banana_sprite(0);
    Sprite *shield = resources_get_shield_sprite();

    /* ── Player 1 hearts (left) ── */
    int lives1 = car1 ? car1->lives : 0;
    for (int i = 0; i < lives1; i++)
        draw_sprite_scaled(heart, HUD_Y + i * (HEART_SIZE + HEART_GAP), HUD_Y, HEART_SIZE, HEART_SIZE);

    /* ── Player 1 effect timers (after hearts) ── */
    int x1 = HUD_Y + lives1 * (HEART_SIZE + HEART_GAP) + EFF_GAP;
    if (banana_ticks1 > 0) {
        draw_effect(banana, banana_ticks1, x1);
        x1 += EFF_BLOCK_W + EFF_GAP;
    }
    if (car1 && car1->shield_ticks > 0)
        draw_effect(shield, car1->shield_ticks, x1);

    /* ── Player 2 hearts (right) ── */
    int lives2 = car2 ? car2->lives : 0;
    for (int i = 0; i < lives2; i++)
        draw_sprite_scaled(heart, SCREEN_W - HUD_Y - (i + 1) * (HEART_SIZE + HEART_GAP), HUD_Y, HEART_SIZE, HEART_SIZE);

    /* ── Player 2 effect timers (before hearts, going right-to-left) ── */
    int x2 = SCREEN_W - HUD_Y - lives2 * (HEART_SIZE + HEART_GAP) - EFF_GAP;
    if (banana_ticks2 > 0) {
        x2 -= EFF_BLOCK_W;
        draw_effect(banana, banana_ticks2, x2);
        x2 -= EFF_GAP;
    }
    if (car2 && car2->shield_ticks > 0) {
        x2 -= EFF_BLOCK_W;
        draw_effect(shield, car2->shield_ticks, x2);
    }
}
