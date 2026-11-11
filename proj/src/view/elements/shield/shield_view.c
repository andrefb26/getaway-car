#include "shield_view.h"
#include "../../../model/resources/resources.h"
#include "../../view.h"

#define SHIELD_DRAW_SIZE 100

void shield_view_draw(Shield *shield) {
    if (!shield || !shield->base.is_active) return;
    Sprite *sp = resources_get_shield_sprite();
    if (!sp) return;
    draw_sprite(sp, (int)shield->base.x + ROAD_OFFSET_X, (int)shield->base.y);
}

void shield_aura_draw(Car *car) {
    if (!car || car->shield_ticks <= 0) return;
    Sprite *sp = resources_get_shield_aura_sprite();
    if (!sp) return;
    int offset = (SHIELD_DRAW_SIZE - sp->width) / 2;
    draw_sprite_scaled(sp,
        (int)car->base.x + ROAD_OFFSET_X - offset,
        (int)car->base.y - offset - TRACK_TILE_HEIGHT / 2,
        SHIELD_DRAW_SIZE, SHIELD_DRAW_SIZE);
}
