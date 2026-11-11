/**
 * @file biome_select_view.h
 * @brief Biome-selection screen rendering.
 */

#ifndef __PROJ_BIOME_SELECT_VIEW_H
#define __PROJ_BIOME_SELECT_VIEW_H

#include "../../../model/terrain/track/track.h"

#define BIOME_LARROW_X      100
#define BIOME_RARROW_X      884
#define BIOME_ARROW_Y       390
#define BIOME_ARROW_HIT      60
#define BIOME_SELECT_BTN_X  384
#define BIOME_SELECT_BTN_Y  650
#define BIOME_SELECT_BTN_W  256
#define BIOME_SELECT_BTN_H   64

/**
 * @brief Draws the biome-selection screen with the currently highlighted biome.
 * @param selected TrackTheme value of the biome currently highlighted by the player.
 */
void biome_select_view_draw(TrackTheme selected);

#endif /* __PROJ_BIOME_SELECT_VIEW_H */
