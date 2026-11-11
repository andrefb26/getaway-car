/**
 * @file cursor.h
 * @brief Mouse cursor model: position tracking and click-edge detection.
 */

#ifndef CURSOR_H
#define CURSOR_H

#include <stdbool.h>

/**
 * @brief Tracks the mouse cursor position and button edge events.
 */
typedef struct {
    int  x;          /**< Current horizontal pixel position (clamped to screen). */
    int  y;          /**< Current vertical pixel position (clamped to screen). */
    int  screen_w;   /**< Screen width used for clamping. */
    int  screen_h;   /**< Screen height used for clamping. */
    bool clicked;    /**< true only on the frame the left button transitions 0→1. */
    bool lb_prev;    /**< Left-button state from the previous packet. */
    bool rb_clicked; /**< true only on the frame the right button transitions 0→1. */
    bool rb_prev;    /**< Right-button state from the previous packet. */
} Cursor;

/**
 * @brief Allocates and initialises a Cursor.
 * @param initial_x Starting horizontal position in pixels.
 * @param initial_y Starting vertical position in pixels.
 * @param screen_w  Screen width for boundary clamping.
 * @param screen_h  Screen height for boundary clamping.
 * @return Pointer to the new Cursor, or NULL on allocation failure.
 */
Cursor* create_cursor(int initial_x, int initial_y, int screen_w, int screen_h);

/**
 * @brief Frees a Cursor.
 * @param cursor Cursor to destroy.
 */
void destroy_cursor(Cursor *cursor);

/**
 * @brief Updates cursor position and button state from a mouse packet.
 * @param cursor     Cursor to update.
 * @param dx         Horizontal displacement from the packet.
 * @param dy         Vertical displacement from the packet.
 * @param lb_current Current left-button state (packet->lb).
 * @param rb_current Current right-button state (packet->rb).
 */
void cursor_update(Cursor *cursor, int dx, int dy, bool lb_current, bool rb_current);

/**
 * @brief Returns the current horizontal pixel position of the cursor.
 * @param cursor Cursor to query.
 * @return X position in pixels.
 */
int  cursor_get_x(const Cursor *cursor);

/**
 * @brief Returns the current vertical pixel position of the cursor.
 * @param cursor Cursor to query.
 * @return Y position in pixels.
 */
int  cursor_get_y(const Cursor *cursor);

/**
 * @brief Returns true if the left mouse button was clicked this frame.
 * @param cursor Cursor to query.
 * @return true on the rising edge of the left button.
 */
bool cursor_left_clicked(const Cursor *cursor);

/**
 * @brief Returns true if the right mouse button was clicked this frame.
 * @param cursor Cursor to query.
 * @return true on the rising edge of the right button.
 */
bool cursor_right_clicked(const Cursor *cursor);

#endif /* CURSOR_H */
