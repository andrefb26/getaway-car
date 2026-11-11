/**
 * @file track.h
 * @brief Logical race track: grid layout, scrolling state, and tile queries.
 */

#ifndef TRACK_H
#define TRACK_H

#include <stdbool.h>

/** @defgroup track_layout Track layout constants
 * @{ */
#define TRACK_LANES            10  /**< Total lanes (5 per player). */
#define TRACK_LANES_PER_PLAYER  5  /**< Lanes assigned to each player. */
#define PLAYER1_LANE_START      0  /**< First lane index for player 1. */
#define PLAYER1_LANE_END        4  /**< Last lane index for player 1. */
#define PLAYER2_LANE_START      5  /**< First lane index for player 2. */
#define PLAYER2_LANE_END        9  /**< Last lane index for player 2. */

#define TRACK_TOTAL_ROWS   200  /**< Total logical rows from start to finish line. */
#define TRACK_VISIBLE_ROWS  12  /**< Rows visible on screen at any one time. */
#define TRACK_TILE_HEIGHT   64  /**< Height of one tile in pixels. */

#define CAR_SCREEN_ROW (TRACK_VISIBLE_ROWS - 2) /**< Screen row at which the car is rendered. */
/** @} */

/**
 * @brief Content type stored in each cell of the track grid.
 */
typedef enum {
    TILE_EMPTY    = 0, /**< Free road — no interaction. */
    TILE_OBSTACLE = 1, /**< Obstacle — damages the car on collision. */
    TILE_BOOST    = 2, /**< Boost — advances the car N logical rows. */
    TILE_FINISH   = 3  /**< Finish line — ends the race. */
} TileType;

/**
 * @brief Visual themes for the track and its lateral scenery.
 */
typedef enum {
    TRACK_THEME_CITY   = 0, /**< Urban environment. */
    TRACK_THEME_DESERT = 1, /**< Desert environment. */
    TRACK_THEME_FOREST = 2, /**< Forest environment. */
    TRACK_THEME_COUNT       /**< Sentinel — total number of themes. */
} TrackTheme;

/**
 * @brief Main track structure holding the grid and scroll state.
 */
typedef struct {
    TileType grid[TRACK_TOTAL_ROWS][TRACK_LANES]; /**< Full logical grid. */
    int      scroll_row;    /**< Logical row at the top of the screen (advances each tick). */
    int      scroll_offset; /**< Sub-tile pixel offset within the current row (0..TRACK_TILE_HEIGHT-1). */
    float    scroll_speed;  /**< Pixels scrolled per tick (track speed). */
    float    scroll_accum;  /**< Fractional pixel accumulator for subpixel scrolling. */
    TrackTheme theme;       /**< Visual theme for this race. */
    bool     infinite;      /**< When true, track scrolls past the finish row indefinitely. */
} Track;

/**
 * @brief Allocates and populates a Track for the given theme.
 * @param theme Visual theme to use.
 * @return Pointer to the new Track, or NULL on allocation failure.
 */
Track* create_track(TrackTheme theme);

/**
 * @brief Frees a Track.
 * @param track Track to destroy.
 */
void   destroy_track(Track *track);

/**
 * @brief Advances the track scroll by one tick.
 *
 * Updates scroll_offset and increments scroll_row when a full tile is crossed.
 * @param track Track to update.
 */
void track_update(Track *track);

/**
 * @brief Returns the tile type at a logical grid position.
 * @param track Track to query.
 * @param row   Logical row (0 = start, TRACK_TOTAL_ROWS-1 = finish).
 * @param lane  Lane index (0–TRACK_LANES-1).
 * @return TileType at (row, lane).
 */
TileType track_get_tile(const Track *track, int row, int lane);

/**
 * @brief Returns the tile type at a visible screen row.
 * @param track      Track to query.
 * @param screen_row Visible row index (0 = top, TRACK_VISIBLE_ROWS-1 = bottom).
 * @param lane       Lane index.
 * @return TileType currently displayed at (screen_row, lane).
 */
TileType track_get_visible_tile(const Track *track, int screen_row, int lane);

/**
 * @brief Checks whether a car in the given lane collides with a tile this tick.
 * @param track Track to query.
 * @param lane  Lane the car occupies.
 * @return Type of the tile collided with, or TILE_EMPTY if no collision.
 */
TileType track_check_car_tile(const Track *track, int lane);

/**
 * @brief Replaces a tile with TILE_EMPTY after it has been collected or hit.
 * @param track Track to modify.
 * @param row   Logical row of the tile.
 * @param lane  Lane of the tile.
 */
void track_clear_tile(Track *track, int row, int lane);

/**
 * @brief Returns true once the scroll has reached the finish line.
 * @param track Track to query.
 * @return true if the race is finished.
 */
bool track_is_finished(const Track *track);

/**
 * @brief Converts a logical row to a screen Y pixel coordinate.
 * @param logical_row  The row index in the track grid.
 * @param scroll_row   The logical row at the top of the screen.
 * @param scroll_offset Sub-tile pixel offset (0..TRACK_TILE_HEIGHT-1).
 * @return Y pixel position of the row's top edge.
 */
static inline double track_row_to_y(int logical_row, int scroll_row, int scroll_offset) {
    int screen_row = logical_row - scroll_row;
    return (double)((2 * CAR_SCREEN_ROW - screen_row) * TRACK_TILE_HEIGHT + scroll_offset);
}

#endif /* TRACK_H */
