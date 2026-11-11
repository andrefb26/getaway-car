/**
 * @file leaderboard_view.h
 * @brief Rendering of the leaderboard screen.
 */

#ifndef LEADERBOARD_VIEW_H
#define LEADERBOARD_VIEW_H

/**
 * @brief Loads all sprites needed by the leaderboard screen.
 *
 * Must be called once before leaderboard_view_draw().
 */
void leaderboard_view_init(void);

/**
 * @brief Draws the full leaderboard screen over the current back-buffer.
 *
 * Renders the background panel centred on screen, followed by column
 * headers and up to MAX_LEADERBOARD data rows read from the global
 * leaderboard singleton.
 */
void leaderboard_view_draw(void);

#endif /* LEADERBOARD_VIEW_H */
