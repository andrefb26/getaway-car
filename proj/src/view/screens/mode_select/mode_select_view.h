/**
 * @file mode_select_view.h
 * @brief Game-mode selection screen rendering.
 */

#ifndef __PROJ_MODE_SELECT_VIEW_H
#define __PROJ_MODE_SELECT_VIEW_H

/**
 * @brief Draws the mode-selection screen with RACE and ENDURANCE cards.
 * @param selection 0 = RACE card highlighted, 1 = ENDURANCE card highlighted.
 */
void mode_select_view_draw(int selection);

#endif /* __PROJ_MODE_SELECT_VIEW_H */
