/**
 * @file scenery_view.h
 * @brief Lateral scenery rendering: draws scrolling trees or cacti beside the road.
 */

#ifndef __PROJ_SCENERY_VIEW_H
#define __PROJ_SCENERY_VIEW_H

#include "../../../model/terrain/scenery/scenery.h"
#include "../../../model/terrain/track/track.h"

/**
 * @brief Draws all active scenery instances at their current screen positions.
 *
 * Chooses the correct sprite (tree vs. cactus) based on the active theme.
 * @param s     Scenery collection to render.
 * @param theme TrackTheme value used to select the sprite.
 */
void scenery_view_draw(const Scenery *s, const Track *track, TrackTheme theme);

#endif /* __PROJ_SCENERY_VIEW_H */
