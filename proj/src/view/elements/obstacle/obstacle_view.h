/**
 * @file obstacle_view.h
 * @brief Obstacle rendering: draws the correct sprite for the active track theme.
 */

#ifndef __PROJ_OBSTACLE_VIEW_H
#define __PROJ_OBSTACLE_VIEW_H

#include "../../../model/elements/obstacle/obstacle.h"

/**
 * @brief Draws the obstacle sprite if the obstacle is active and on screen.
 *
 * Selects the rock, barrel, or banana sprite based on obstacle type and theme.
 * @param obs   Obstacle to render.
 * @param theme TrackTheme value used to pick the themed sprite.
 */
void obstacle_view_draw(Obstacle *obs, int theme);

#endif /* __PROJ_OBSTACLE_VIEW_H */
