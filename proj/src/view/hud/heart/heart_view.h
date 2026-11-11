/**
 * @file heart_view.h
 * @brief Life-counter rendering: draws heart icons for each remaining life.
 */

#ifndef __PROJ_HEART_VIEW_H
#define __PROJ_HEART_VIEW_H

#include "../../../model/elements/car/car.h"

/**
 * @brief Draws heart icons reflecting the remaining lives of both players.
 *
 * Player 1's hearts are drawn on the left side of the HUD bar;
 * player 2's on the right.
 * @param car1          Player 1 car (read-only).
 * @param car2          Player 2 car (read-only).
 * @param banana_ticks1 Remaining inverted-control ticks for player 1 (shown as banana icon).
 * @param banana_ticks2 Remaining inverted-control ticks for player 2 (shown as banana icon).
 */
void heart_view_draw(const Car *car1, const Car *car2, int banana_ticks1, int banana_ticks2);

#endif /* __PROJ_HEART_VIEW_H */
