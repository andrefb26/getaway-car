/**
 * @file view.h
 * @brief Core rendering primitives: double-buffered frame management and drawing.
 *
 * Screen layout: 192 px lateral grass | 640 px road (10 × 64) | 192 px lateral grass.
 */

#ifndef __PROJ_VIEW_H
#define __PROJ_VIEW_H

#include "../model/common/sprite/sprite.h"
#include "../model/elements/car/car.h"
#include "../model/elements/obstacle/obstacle.h"
#include "../controller/palette/palette.h"

#define ROAD_OFFSET_X 192 /**< X pixel offset where the road area begins. */

/**
 * @brief Allocates the off-screen back buffer used for double buffering.
 */
void view_init_buffers(void);

/**
 * @brief Blits a sprite at the given screen position.
 *
 * Pixels with index PAL_TRANSPARENT are skipped.
 * @param sp Sprite to draw.
 * @param x  Left edge X position in pixels.
 * @param y  Top edge Y position in pixels.
 */
void draw_sprite(Sprite *sp, int x, int y);

/**
 * @brief Blits a sprite scaled to the given dimensions.
 *
 * Uses nearest-neighbour scaling.
 * @param sp Sprite to draw.
 * @param x  Left edge X position in pixels.
 * @param y  Top edge Y position in pixels.
 * @param w  Target width in pixels.
 * @param h  Target height in pixels.
 */
void draw_sprite_scaled(Sprite *sp, int x, int y, int w, int h);

/**
 * @brief Fills a rectangle with a flat palette colour.
 * @param x     Left edge X position in pixels.
 * @param y     Top edge Y position in pixels.
 * @param w     Width in pixels.
 * @param h     Height in pixels.
 * @param color Palette index to fill with.
 */
void draw_rect(int x, int y, int w, int h, uint8_t color);

/**
 * @brief Clears the entire back buffer to a single palette colour.
 * @param color_index Palette index to fill with.
 */
void draw_clear(uint8_t color_index);

/**
 * @brief Copies the back buffer to the video memory frame buffer (page flip).
 */
void copy_buffer_to_video(void);

#endif /* __PROJ_VIEW_H */
