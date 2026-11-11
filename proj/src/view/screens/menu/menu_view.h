/**
 * @file menu_view.h
 * @brief Main menu screen rendering.
 */

#ifndef __PROJ_MENU_VIEW_H
#define __PROJ_MENU_VIEW_H


/**
 * @brief Draws the main menu screen.
 *
 * Renders the title, START, LEADERBOARD and EXIT buttons with the selected one highlighted.
 * @param selection 0=START, 1=LEADERBOARD, 2=EXIT.
 */
void menu_view_draw(int selection);

#endif /* __PROJ_MENU_VIEW_H */
