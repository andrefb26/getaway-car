/**
 * @file car_view.h
 * @brief Car rendering: draws a car sprite at its current screen position.
 */

#ifndef __PROJ_CAR_VIEW_H
#define __PROJ_CAR_VIEW_H

#include "../../../model/elements/car/car.h"
#include "../../../model/terrain/track/track.h"

/**
 * @brief Draws the car sprite corresponding to its current CarState.
 * @param car   Car to render.
 * @param theme Track theme (determines which colour variant to use).
 */
void car_view_draw(Car *car, TrackTheme theme);

#endif /* __PROJ_CAR_VIEW_H */
