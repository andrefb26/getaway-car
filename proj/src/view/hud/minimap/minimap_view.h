/**
 * @file minimap_view.h
 * @brief Race-progress minimap rendering (race mode only).
 */

#ifndef __PROJ_MINIMAP_VIEW_H
#define __PROJ_MINIMAP_VIEW_H

#include "../../../model/elements/car/car.h"
#include "../../../model/terrain/track/track.h"

/**
 * @brief Draws the race progress minimap in the top-left corner (race mode only).
 *
 * Renders a vertical strip representing the 200-row track from start (bottom)
 * to finish (top), with a blue dot for player 1 and a red dot for player 2.
 */
void minimap_view_draw(const Car *car1, const Car *car2, const Track *track);

#endif /* __PROJ_MINIMAP_VIEW_H */
