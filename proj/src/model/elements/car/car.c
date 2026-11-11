#include "car.h"
#include <stdlib.h>
#include "../../terrain/track/track.h"

Car* create_car(int initial_lane, int lane_min, int lane_max, int car_width, int car_height) {
    Car* car = (Car*) malloc(sizeof(Car));
    if (car == NULL) return NULL;

    init_element(&car->base, car_lane_to_x(initial_lane),
                 (double)(CAR_SCREEN_ROW * TRACK_TILE_HEIGHT), car_width, car_height);

    car->lane             = initial_lane;
    car->track_progress   = 0;
    car->boost_remaining  = 0.0f;
    car->state            = CAR_STATE_NORMAL;
    car->lane_min = lane_min;
    car->lane_max = lane_max;
    car->exploding        = false;
    car->shield_ticks     = 0;
    car_init_session(car, CAR_INITIAL_LIVES);

    return car;
}

void destroy_car(Car* car) {
    if (car != NULL) {
        free(car);
    }
}

void car_move_lane(Car* car, int direction) {
    if (car == NULL || !car->base.is_active) return;
    if (car->state == CAR_STATE_EXPLODED)    return;

    int new_lane = car->lane + direction;
    if (new_lane < car->lane_min || new_lane > car->lane_max) return;

    car->lane   = new_lane;
    car->base.x = car_lane_to_x(new_lane);
}

void car_take_damage(Car* car) {
    if (car == NULL || !car->base.is_active) return;
    if (car->shield_ticks > 0) { car->shield_ticks = 0; return; }

    if (car->lives > 0) car->lives--;

    // Knockback: move down one tile, capped so the car stays fully visible
    int max_y = (TRACK_VISIBLE_ROWS - 1) * TRACK_TILE_HEIGHT;
    if (car->base.y + TRACK_TILE_HEIGHT <= (double)max_y)
        car->base.y += TRACK_TILE_HEIGHT;

    switch (car->state) {
        case CAR_STATE_NORMAL:
            car->state = CAR_STATE_DAMAGED;
            break;
        case CAR_STATE_DAMAGED:
            car->state = CAR_STATE_BURNING;
            break;
        case CAR_STATE_BURNING:
            car->state          = CAR_STATE_EXPLODED;
            car->base.is_active = false; // Retira o carro do jogo
            break;
        case CAR_STATE_EXPLODED:
        default:
            break;
    }
}

void car_banana_slip(Car* car) {
    if (car == NULL || !car->base.is_active) return;
    if (car->state == CAR_STATE_EXPLODED)    return;

    int dir = (rand() % 2) ? -1 : 1;
    int new_lane = car->lane + dir;
    if (new_lane < car->lane_min || new_lane > car->lane_max)
        new_lane = car->lane - dir;   /* tenta a direção oposta */
    if (new_lane >= car->lane_min && new_lane <= car->lane_max) {
        car->lane   = new_lane;
        car->base.x = car_lane_to_x(new_lane);
    }
}

void car_apply_boost(Car* car, int tiles) {
    if (car == NULL || !car->base.is_active) return;
    if (car->state == CAR_STATE_EXPLODED)    return;

    car->track_progress  += tiles;
    car->boost_remaining += (float)(tiles * TRACK_TILE_HEIGHT);
}

void reset_car(Car* car, int initial_lane) {
    if (car == NULL) return;

    car->lane             = initial_lane;
    car->base.x           = car_lane_to_x(initial_lane);
    car->base.y           = (double)(CAR_SCREEN_ROW * TRACK_TILE_HEIGHT);
    car->base.is_active   = true;
    car->track_progress   = 0;
    car->boost_remaining  = 0.0f;
    car->state            = CAR_STATE_NORMAL;
    car->exploding        = false;
    car->shield_ticks     = 0;
    car_init_session(car, CAR_INITIAL_LIVES);
}

void car_init_session(Car* car, int initial_lives) {
    if (car == NULL) return;
    car->score = 0;
    car->lives = initial_lives;
}

void car_apply_shield(Car* car, int ticks) {
    if (car == NULL || !car->base.is_active) return;
    if (car->state == CAR_STATE_EXPLODED)    return;
    car->shield_ticks = ticks;
}
