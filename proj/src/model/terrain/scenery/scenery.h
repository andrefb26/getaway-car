/**
 * @file scenery.h
 * @brief Lateral scenery: tree/cactus instances that scroll alongside the track.
 */

#ifndef __PROJ_SCENERY_H
#define __PROJ_SCENERY_H

#include "../track/track.h"

#define MAX_TREES 120 /**< Maximum number of scenery instances alive at once. */
#define TREE_SIZE  32 /**< Sprite width/height of one scenery object in pixels. */

/**
 * @brief One scenery sprite instance placed beside the track.
 */
typedef struct {
    int    screen_x;    /**< Horizontal pixel position (fixed at spawn). */
    double screen_y;    /**< Vertical pixel position, updated each tick by scenery_update. */
    int    logical_row; /**< World row at spawn — used for tile variant and scroll calc. */
} TreeInstance;

/**
 * @brief Collection of all active scenery instances and their shared scroll state.
 */
typedef struct {
    TreeInstance trees[MAX_TREES]; /**< Array of active scenery instances. */
    int          count;            /**< Number of currently active instances. */
    float        scroll_offset;    /**< Current sub-tile scroll offset in pixels. */
} Scenery;

/**
 * @brief Allocates and initialises a Scenery collection.
 * @param theme Track theme that determines which sprites are used.
 * @return Pointer to the new Scenery, or NULL on allocation failure.
 */
Scenery* scenery_create(TrackTheme theme);

/**
 * @brief Synchronises the scenery positions with the current track scroll.
 *
 * Spawns new instances at the bottom and removes those that scroll off the top.
 * @param s     Scenery collection to update.
 * @param track Current track (provides scroll_row and scroll_offset).
 */
void     scenery_update(Scenery *s, const Track *track);

/**
 * @brief Frees a Scenery collection.
 * @param s Scenery to destroy.
 */
void     scenery_destroy(Scenery *s);

#endif /* __PROJ_SCENERY_H */
