/**
 * @file shield_view.h
 * @brief Shield pickup rendering.
 */

#ifndef __PROJ_SHIELD_VIEW_H
#define __PROJ_SHIELD_VIEW_H

#include "../../../model/elements/shield/shield.h"
#include "../../../model/elements/car/car.h"

/**
 * @brief Draws the shield pickup sprite if it is active and on screen.
 * @param shield Shield to render.
 */
void shield_view_draw(Shield *shield);

/**
 * @brief Draws the yellow aura overlay on a car while its shield is active.
 * @param car Car to render the aura on (skipped if shield_ticks == 0).
 */
void shield_aura_draw(Car *car);

#endif /* __PROJ_SHIELD_VIEW_H */
