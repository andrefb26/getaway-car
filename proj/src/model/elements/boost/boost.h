/**
 * @file boost.h
 * @brief Boost pickup: a one-tile collectible that advances the car's progress.
 */

#ifndef BOOST_H
#define BOOST_H

#include "../../common/element/element.h"
#include "../../terrain/track/track.h"
#include "../car/car.h"

/**
 * @brief Represents a boost pickup on the track.
 *
 * Occupies exactly one lane × one tile. When a car drives over it,
 * the car's track_progress is advanced and the boost is deactivated.
 */
typedef struct {
    Element base;       /**< Pixel position, hitbox, active flag, and sprite. */
    int     lane;       /**< Logical lane index (0–9). */
    int     row;        /**< Logical row index in the track grid. */
    int     sprite_idx; /**< Which city boost sprite to use (0-2). */
} Boost;

/**
 * @brief Allocates and initialises a Boost at the given grid position.
 * @param row  Logical row in the track grid.
 * @param lane Logical lane index.
 * @return Pointer to the new Boost, or NULL on allocation failure.
 */
Boost* create_boost(int row, int lane);

/**
 * @brief Frees a Boost.
 * @param boost Boost to destroy.
 */
void   destroy_boost(Boost *boost);

/**
 * @brief Updates the pixel position of the boost based on the current track scroll.
 *
 * Automatically deactivates the boost when it scrolls off the top of the screen.
 * @param boost         Boost to update.
 * @param scroll_row    Current logical row at the top of the screen.
 * @param scroll_offset Sub-tile pixel offset (0..TRACK_TILE_HEIGHT-1).
 */
void boost_update(Boost *boost, int scroll_row, int scroll_offset);

/**
 * @brief Checks whether the boost is within the visible screen area.
 * @param boost Boost to test.
 * @return true if the boost is on screen.
 */
bool boost_is_visible(const Boost *boost);

/**
 * @brief AABB + lane collision check between a boost and a car.
 * @param boost Boost to test.
 * @param car   Car to test against.
 * @return true if the car overlaps the boost.
 */
bool boost_collides_with_car(const Boost *boost, const Car *car);

#endif /* BOOST_H */
