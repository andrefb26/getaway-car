#include "car_view.h"
#include "../../../model/resources/resources.h"
#include "../../view.h"

#define CAR_DRAW_SIZE 100

void car_view_draw(Car *car, TrackTheme theme) {
    if (!car) return;
    Sprite *sp = resources_get_car_sprite(car->player - 1, car->state);
    if (!sp) return;
    int offset = (CAR_DRAW_SIZE - sp->width) / 2;
    (void)theme;
    draw_sprite_scaled(sp,
        (int)car->base.x + ROAD_OFFSET_X - offset,
        (int)car->base.y - offset,
        CAR_DRAW_SIZE, CAR_DRAW_SIZE);
}
