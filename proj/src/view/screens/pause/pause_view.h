/**
 * @file pause_view.h
 * @brief Pause-menu overlay rendering.
 */

#ifndef __PROJ_PAUSE_VIEW_H
#define __PROJ_PAUSE_VIEW_H

/** @defgroup pause_layout Pause panel layout constants (screen 1024×768)
 * @{ */
#define PAUSE_PANEL_W   300 /**< Panel width in pixels. */
#define PAUSE_PANEL_H   200 /**< Panel height in pixels. */
#define PAUSE_PANEL_X   362 /**< Panel left edge: (1024 - 300) / 2. */
#define PAUSE_PANEL_Y   284 /**< Panel top edge: (768 - 200) / 2. */
#define PAUSE_BTN_W     200 /**< Button width in pixels. */
#define PAUSE_BTN_H      44 /**< Button height in pixels. */
#define PAUSE_BTN_X     412 /**< Button left edge: PAUSE_PANEL_X + (300 - 200) / 2. */
#define PAUSE_RESUME_Y  356 /**< RESUME button top edge: PAUSE_PANEL_Y + 72. */
#define PAUSE_QUIT_Y    414 /**< QUIT button top edge: PAUSE_RESUME_Y + 44 + 14. */
/** @} */

/**
 * @brief Draws the pause overlay panel with RESUME and QUIT buttons.
 * @param selected 0 = RESUME highlighted, 1 = QUIT highlighted.
 */
void pause_view_draw(int selected);

#endif /* __PROJ_PAUSE_VIEW_H */
