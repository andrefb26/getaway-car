/**
 * @file win_view.h
 * @brief Win/result screen rendering: winner image and interactive buttons.
 */

#ifndef __PROJ_WIN_VIEW_H
#define __PROJ_WIN_VIEW_H

#define WIN_SCREEN_W     1024

#define WIN_IMG_W         400
#define WIN_IMG_H         400
#define WIN_IMG_X        ((WIN_SCREEN_W - WIN_IMG_W) / 2)   /**< 312 */
#define WIN_IMG_Y          80

#define WIN_BTN_W         256
#define WIN_BTN_H          64
#define WIN_BTN_GAP        64
#define WIN_BTNS_TOTAL_W  (WIN_BTN_W + WIN_BTN_GAP + WIN_BTN_W)
#define WIN_PLAY_X       ((WIN_SCREEN_W - WIN_BTNS_TOTAL_W) / 2)   /**< 224 */
#define WIN_MENU_X       (WIN_PLAY_X + WIN_BTN_W + WIN_BTN_GAP)    /**< 544 */
#define WIN_BTN_Y         580
#define WIN_BORDER_T        4

/* Draw screen: two images side by side */
#define WIN_DRAW_IMG_W   300
#define WIN_DRAW_IMG_H   300
#define WIN_DRAW_GAP      24
#define WIN_DRAW_X       ((WIN_SCREEN_W - 2*WIN_DRAW_IMG_W - WIN_DRAW_GAP) / 2)
#define WIN_DRAW_Y        100

/**
 * @brief Draws the win screen with winner image and interactive buttons.
 * @param winner   1=P1(blue) 2=P2(red).
 * @param selected 0=PLAY AGAIN highlighted, 1=MENU highlighted.
 */
void win_view_draw(int winner, int selected);

#endif /* __PROJ_WIN_VIEW_H */
