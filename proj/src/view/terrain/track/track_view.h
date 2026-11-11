/**
 * @file track_view.h
 * @brief Track rendering: draws the road tiles, lane markings, and finish line.
 */

#ifndef __PROJ_TRACK_VIEW_H
#define __PROJ_TRACK_VIEW_H

#include "../../../model/terrain/track/track.h"

/**
 * @brief Draws the full visible portion of the track for the current scroll state.
 *
 * Selects tile sprites according to the track theme and renders the lateral
 * grass/sand strips on either side of the road.
 * @param track Track to render (read-only).
 */
void track_view_draw(const Track *track);

#endif /* __PROJ_TRACK_VIEW_H */
