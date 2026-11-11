/**
 * @file sprite.h
 * @brief Sprite loading and memory management from XPM pixel maps.
 */

#ifndef __PROJ_SPRITE_H
#define __PROJ_SPRITE_H

#include <stddef.h>
#include <stdint.h>
#include <lcom/xpm.h>

/**
 * @brief An indexed-colour sprite loaded from an XPM pixel map.
 */
typedef struct {
    int width;      /**< Width in pixels. */
    int height;     /**< Height in pixels. */
    uint8_t *pixmap; /**< Palette indices, 1 byte per pixel (XPM_INDEXED). */
} Sprite;

/**
 * @brief Creates a Sprite from an XPM map.
 * @param map XPM pixel map to load.
 * @return Pointer to the allocated Sprite, or NULL on failure.
 */
Sprite* create_sprite(xpm_map_t map);

/**
 * @brief Frees a Sprite and its pixel buffer.
 * @param sp Sprite to destroy (may be NULL).
 */
void    sprite_destroy(Sprite *sp);

#endif /* __PROJ_SPRITE_H */
