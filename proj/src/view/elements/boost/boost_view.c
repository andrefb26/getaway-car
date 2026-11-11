#include "boost_view.h"
#include "../../../model/resources/resources.h"
#include "../../view.h"

void boost_view_draw(Boost *boost) {
    if (!boost || !boost->base.is_active) return;
    Sprite *sp = resources_get_city_boost_sprite(boost->sprite_idx);
    if (!sp) return;
    draw_sprite(sp, (int)boost->base.x + ROAD_OFFSET_X, (int)boost->base.y);
}
