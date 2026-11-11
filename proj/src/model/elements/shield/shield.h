/**
 * @file shield.h
 * @brief Shield pickup: grants the collecting car 5 seconds of invulnerability.
 */

#ifndef SHIELD_H
#define SHIELD_H

#include "../../common/element/element.h"
#include "../../terrain/track/track.h"
#include "../car/car.h"

#define SHIELD_DURATION_TICKS 300 /**< 5 seconds at 60 Hz. */

/**
 * @brief Represents a shield pickup on the track.
 */
typedef struct {
    Element base; /**< Pixel position, hitbox, active flag, and sprite. */
    int     lane; /**< Logical lane index (0–9). */
    int     row;  /**< Logical row index in the track grid. */
} Shield;

/**
 * @brief Allocates and initialises a Shield at the given grid position.
 * @param row  Logical row in the track grid.
 * @param lane Logical lane index.
 * @return Pointer to the new Shield, or NULL on allocation failure.
 */
Shield* create_shield(int row, int lane);

/**
 * @brief Frees a Shield.
 * @param shield Shield to destroy.
 */
void    destroy_shield(Shield *shield);

/**
 * @brief Updates the pixel position of the shield based on the current track scroll.
 *
 * Automatically deactivates the shield when it scrolls off the top of the screen.
 * @param shield        Shield to update.
 * @param scroll_row    Current logical row at the top of the screen.
 * @param scroll_offset Sub-tile pixel offset (0..TRACK_TILE_HEIGHT-1).
 */
void    shield_update(Shield *shield, int scroll_row, int scroll_offset);

/**
 * @brief Checks whether the shield is within the visible screen area.
 * @param shield Shield to test.
 * @return true if the shield is on screen.
 */
bool    shield_is_visible(const Shield *shield);

/**
 * @brief AABB + lane collision check between a shield pickup and a car.
 * @param shield Shield to test.
 * @param car    Car to test against.
 * @return true if the car overlaps the shield pickup.
 */
bool    shield_collides_with_car(const Shield *shield, const Car *car);

#endif /* SHIELD_H */
