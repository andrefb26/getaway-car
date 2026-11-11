/**
 * @file timer_view.h
 * @brief Timer rendering: displays the elapsed race time in MM:SS format on the HUD.
 */

#ifndef __PROJ_TIMER_VIEW_H
#define __PROJ_TIMER_VIEW_H

#include <stdint.h>

#define HUD_BAR_H 64 /**< Height of the HUD bar in pixels. */

/**
 * @brief Draws the elapsed race time at the centre of the top HUD bar.
 *
 * Converts elapsed_ticks (at 60 Hz) to minutes and seconds and renders
 * each digit using the digit sprites from the resource cache.
 * @param elapsed_ticks Number of game ticks elapsed since the race started.
 */
void timer_view_draw(uint32_t elapsed_ticks);

#endif /* __PROJ_TIMER_VIEW_H */
