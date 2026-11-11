#include "boost.h"
#include <stdlib.h>

Boost* create_boost(int row, int lane) {
    Boost* boost = (Boost*) malloc(sizeof(Boost));
    if (boost == NULL) return NULL;

    boost->lane       = lane;
    boost->row        = row;
    boost->sprite_idx = rand() % 3;

    double x = car_lane_to_x(lane);
    double y = (double)(row * TRACK_TILE_HEIGHT);

    init_element(&boost->base, x, y, CAR_LANE_WIDTH, TRACK_TILE_HEIGHT);

    return boost;
}

void destroy_boost(Boost* boost) {
    if (boost != NULL)
        free(boost);
}

void boost_update(Boost* boost, int scroll_row, int scroll_offset) {
    if (boost == NULL || !boost->base.is_active) return;

    boost->base.y = track_row_to_y(boost->row, scroll_row, scroll_offset);

    if (boost->base.y > (double)(TRACK_VISIBLE_ROWS * TRACK_TILE_HEIGHT))
        boost->base.is_active = false;
}

bool boost_is_visible(const Boost* boost) {
    if (boost == NULL || !boost->base.is_active) return false;

    int screen_height = TRACK_VISIBLE_ROWS * TRACK_TILE_HEIGHT;
    return boost->base.y < screen_height && boost->base.y + boost->base.height > 0;
}

bool boost_collides_with_car(const Boost* boost, const Car* car) {
    if (boost == NULL || !boost->base.is_active) return false;
    if (car  == NULL || !car->base.is_active)    return false;

    if (car->lane != boost->lane) return false;

    int car_y_top   = (int)car->base.y;
    int car_y_bot   = car_y_top + CAR_HEIGHT;
    int boost_y_top = (int)boost->base.y;
    int boost_y_bot = boost_y_top + (int)boost->base.height;

    return car_y_top < boost_y_bot && car_y_bot > boost_y_top;
}
