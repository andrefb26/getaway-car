/**
 * @file obstacle.h
 * @brief Obstacle model: single-tile hazards that damage or deflect a car.
 */

#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "../../common/element/element.h"
#include "../../terrain/track/track.h"
#include "../car/car.h"

/**
 * @brief Behaviour type of an obstacle on collision.
 */
typedef enum {
    OBSTACLE_ROCK   = 0, /**< Concrete block — deals damage to the car. */
    OBSTACLE_BANANA = 1, /**< Banana peel — causes the car to slip sideways. */
    OBSTACLE_OIL    = 2, /**< Oil puddle — causes the car to slip sideways. */
} ObstacleType;

/**
 * @brief Represents a single-tile obstacle on the track.
 *
 * Always occupies one lane × one row. Multi-tile clusters are composed in game.c.
 */
typedef struct {
    Element      base;       /**< Pixel position, hitbox, active flag, and sprite. */
    int          lane;       /**< Logical lane index. */
    int          row;        /**< Logical row index in the track grid. */
    ObstacleType type;       /**< Effect applied when a car collides with this obstacle. */
    int          sprite_idx; /**< Which city obstacle sprite to use (0-15). */
} Obstacle;

/**
 * @brief Allocates and initialises an Obstacle at the given grid position.
 * @param row  Logical row in the track grid.
 * @param lane Logical lane index.
 * @param type Collision behaviour.
 * @return Pointer to the new Obstacle, or NULL on allocation failure.
 */
Obstacle* create_obstacle(int row, int lane, ObstacleType type);

/**
 * @brief Frees an Obstacle.
 * @param obs Obstacle to destroy.
 */
void      destroy_obstacle(Obstacle *obs);

/**
 * @brief Updates the pixel position of the obstacle based on the current track scroll.
 *
 * Must be called once per tick before drawing.
 * @param obs           Obstacle to update.
 * @param scroll_row    Current logical row at the top of the screen.
 * @param scroll_offset Sub-tile pixel offset (0..TRACK_TILE_HEIGHT-1).
 */
void obstacle_update(Obstacle *obs, int scroll_row, int scroll_offset);

/**
 * @brief Checks whether the obstacle is within the visible screen area.
 * @param obs Obstacle to test.
 * @return true if the obstacle is on screen.
 */
bool obstacle_is_visible(const Obstacle *obs);

/**
 * @brief AABB collision check between an obstacle and a car.
 * @param obs Obstacle to test.
 * @param car Car to test against.
 * @return true if the car overlaps the obstacle.
 */
bool obstacle_collides_with_car(const Obstacle *obs, const Car *car);

#endif /* OBSTACLE_H */
