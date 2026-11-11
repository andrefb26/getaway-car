/**
 * @file input.h
 * @brief Input abstraction: keyboard and mouse events mapped to game actions.
 */

#ifndef __PROJ_INPUT_H
#define __PROJ_INPUT_H

#include <stdint.h>
#include <stdbool.h>

/** @defgroup input_init Input initialisation
 * @{ */

/**
 * @brief Processes the latest keyboard scancode and updates extended-key state.
 *
 * Must be called at the end of every keyboard interrupt handler.
 */
void input_update(void);

/**
 * @brief Initialises the global mouse cursor at the given screen position.
 * @param screen_w Screen width in pixels (used for boundary clamping).
 * @param screen_h Screen height in pixels (used for boundary clamping).
 */
void input_init_cursor(int screen_w, int screen_h);

/**
 * @brief Updates cursor position and button state from a complete mouse packet.
 * @param dx Horizontal displacement from the packet.
 * @param dy Vertical displacement from the packet.
 * @param lb Current left-button state.
 * @param rb Current right-button state.
 */
void input_mouse_update(int dx, int dy, bool lb, bool rb);

/**
 * @brief Clears all accumulated input state (called between game ticks).
 */
void input_flush(void);

/** @} */

/** @defgroup input_banana Banana power-up (inverted controls)
 * @{ */

/**
 * @brief Inverts player 1's controls for the given number of ticks.
 * @param ticks Duration of the inverted-control effect.
 */
void input_set_car1_inverted(int ticks);

/**
 * @brief Inverts player 2's controls for the given number of ticks.
 * @param ticks Duration of the inverted-control effect.
 */
void input_set_car2_inverted(int ticks);

/** @brief Returns the remaining inversion ticks for player 1 (0 = no effect). */
int input_get_car1_inverted_ticks(void);

/** @brief Returns the remaining inversion ticks for player 2 (0 = no effect). */
int input_get_car2_inverted_ticks(void);

/**
 * @brief Decrements the inversion countdown timers by one tick.
 *
 * Must be called once per game tick.
 */
void input_tick_inverted(void);

/** @} */

/** @defgroup input_global Global state queries
 * @{ */

/**
 * @brief Returns true if the ESC key was pressed this frame.
 * @return Non-zero on press.
 */
int input_esc_pressed(void);

/** @} */

/** @defgroup input_menu Menu / game-over combined checks
 * @{ */

/**
 * @brief Returns true if the start action was triggered (keyboard or mouse).
 * @return Non-zero if start was pressed.
 */
int input_menu_start_pressed(void);

/**
 * @brief Returns true if the restart action was triggered on the game-over screen.
 * @return Non-zero if restart was pressed.
 */
int input_gameover_restart_pressed(void);

/**
 * @brief Returns true if the return-to-menu action was triggered on the game-over screen.
 * @return Non-zero if menu was pressed.
 */
int input_gameover_menu_pressed(void);

/** @} */

/** @defgroup input_keyboard Raw keyboard action checks
 * @{ */

/** @brief Returns non-zero if the keyboard start key was pressed. */
int input_keyboard_start_pressed(void);

/** @brief Returns non-zero if the keyboard restart key was pressed. */
int input_keyboard_restart_pressed(void);

/** @brief Returns non-zero if the keyboard menu key was pressed. */
int input_keyboard_menu_pressed(void);

/** @brief Returns non-zero if the single-player car-left key was pressed. */
int input_keyboard_car_left_pressed(void);

/** @brief Returns non-zero if the single-player car-right key was pressed. */
int input_keyboard_car_right_pressed(void);

/** @brief Returns non-zero if player 1's left key was pressed. */
int input_keyboard_car1_left_pressed(void);

/** @brief Returns non-zero if player 1's right key was pressed. */
int input_keyboard_car1_right_pressed(void);

/** @brief Returns non-zero if the pause key was pressed. */
int input_keyboard_pause_pressed(void);

/** @brief Returns non-zero if the up arrow was pressed. */
int input_keyboard_up_pressed(void);

/** @brief Returns non-zero if the down arrow was pressed. */
int input_keyboard_down_pressed(void);

/** @brief Returns non-zero if the confirm/enter key was pressed. */
int input_keyboard_confirm_pressed(void);

/** @} */

/** @defgroup input_nav Menu keyboard navigation
 * @{ */

/** @brief Returns non-zero if the menu up navigation key was pressed. */
int input_menu_nav_up(void);

/** @brief Returns non-zero if the menu down navigation key was pressed. */
int input_menu_nav_down(void);

/** @brief Returns non-zero if the menu left navigation key was pressed. */
int input_menu_nav_left(void);

/** @brief Returns non-zero if the menu right navigation key was pressed. */
int input_menu_nav_right(void);

/** @} */

/** @defgroup input_mode_select Mode-selection screen
 * @{ */

/** @brief Returns non-zero if the mode-select left key was pressed. */
int input_mode_nav_left(void);

/** @brief Returns non-zero if the mode-select right key was pressed. */
int input_mode_nav_right(void);

/** @brief Returns non-zero if the cursor is hovering over the RACE card. */
int input_mouse_over_race_card(void);

/** @brief Returns non-zero if the cursor is hovering over the ENDURANCE card. */
int input_mouse_over_endurance_card(void);

/** @brief Returns non-zero if the RACE card was clicked this frame. */
int input_mouse_race_card_pressed(void);

/** @brief Returns non-zero if the ENDURANCE card was clicked this frame. */
int input_mouse_endurance_card_pressed(void);

/** @} */

/** @defgroup input_gameplay Gameplay mouse control
 * @{ */

/**
 * @brief Consumes accumulated horizontal mouse movement and returns a left-move signal for car 2.
 * @return Non-zero if the accumulated delta is sufficient for a left lane change.
 */
int input_mouse_car2_left(void);

/**
 * @brief Consumes accumulated horizontal mouse movement and returns a right-move signal for car 2.
 * @return Non-zero if the accumulated delta is sufficient for a right lane change.
 */
int input_mouse_car2_right(void);

/** @} */

/** @defgroup input_mouse_menu Main-menu mouse checks
 * @{ */

/** @brief Returns non-zero if the cursor is over the START button. */
int input_mouse_over_start(void);

/** @brief Returns non-zero if the cursor is over the INSTRUCTIONS button. */
int input_mouse_over_instructions(void);

/** @brief Returns non-zero if the INSTRUCTIONS button was clicked this frame. */
int input_mouse_instructions_pressed(void);

/** @brief Returns non-zero if the cursor is over the EXIT button. */
int input_mouse_over_exit(void);

/** @brief Returns non-zero if the START button was clicked this frame. */
int input_mouse_start_pressed(void);

/** @brief Returns non-zero if the EXIT button was clicked this frame. */
int input_mouse_exit_pressed(void);

/** @brief Returns non-zero if the RESTART button was clicked on the result screen. */
int input_mouse_restart_pressed(void);

/** @brief Returns non-zero if the MENU button was clicked on the result screen. */
int input_mouse_menu_pressed(void);

/** @} */

/** @defgroup input_mouse_pause Pause-menu mouse checks
 * @{ */

/** @brief Returns non-zero if the cursor is over the RESUME button. */
int input_mouse_over_pause_resume(void);

/** @brief Returns non-zero if the cursor is over the QUIT button. */
int input_mouse_over_pause_quit(void);

/** @brief Returns non-zero if the RESUME button was clicked this frame. */
int input_mouse_pause_resume_pressed(void);

/** @brief Returns non-zero if the QUIT button was clicked this frame. */
int input_mouse_pause_quit_pressed(void);

/** @} */

/** @defgroup input_mouse_win Win-screen mouse checks
 * @{ */

/** @brief Returns non-zero if the cursor is over the PLAY AGAIN button. */
int input_mouse_over_win_play_again(void);

/** @brief Returns non-zero if the cursor is over the MENU button. */
int input_mouse_over_win_menu(void);

/** @brief Returns non-zero if the PLAY AGAIN button was clicked this frame. */
int input_mouse_win_play_again_pressed(void);

/** @brief Returns non-zero if the MENU button was clicked this frame. */
int input_mouse_win_menu_pressed(void);

/** @} */

/** @defgroup input_leaderboard Leaderboard screen
 * @{ */

/**
 * @brief Returns non-zero if the leaderboard back action was triggered.
 *
 * Mapped to the ESC key; used to return to the main menu from the leaderboard.
 * @return Non-zero on press.
 */
int input_leaderboard_back_pressed(void);

/** @brief Returns non-zero if the LEADERBOARD button was clicked on the main menu. */
int input_mouse_leaderboard_pressed(void);

/** @brief Returns non-zero if the cursor is over the LEADERBOARD button on the main menu. */
int input_mouse_over_leaderboard(void);

/** @} */

/** @defgroup input_cursor Cursor position
 * @{ */

/**
 * @brief Returns the current cursor X position in pixels.
 * @return Horizontal pixel position.
 */
int input_cursor_x(void);

/**
 * @brief Returns the current cursor Y position in pixels.
 * @return Vertical pixel position.
 */
int input_cursor_y(void);

/** @} */

/** @defgroup input_biome_select Biome-selection screen navigation
 * @{ */

/** @brief Returns non-zero if the biome left key was pressed (A or left arrow). */
int input_biome_nav_left(void);

/** @brief Returns non-zero if the biome right key was pressed (D or right arrow). */
int input_biome_nav_right(void);

/** @brief Returns non-zero if the biome confirm key was pressed (ENTER). */
int input_biome_select_pressed(void);

/** @brief Returns non-zero if the cursor is hovering over the SELECT button on the biome screen. */
int input_mouse_over_biome_select(void);

/** @brief Returns non-zero if the SELECT button was clicked on the biome screen. */
int input_mouse_biome_select_pressed(void);

/** @brief Returns non-zero if the left arrow area was clicked on the biome screen. */
int input_mouse_biome_arrow_left(void);

/** @brief Returns non-zero if the right arrow area was clicked on the biome screen. */
int input_mouse_biome_arrow_right(void);

/** @} */

/** @defgroup input_car_select Car-selection screen navigation
 * @{ */

/** @brief Returns non-zero if player 1 pressed left on the car-select screen. */
int input_p1_nav_left(void);

/** @brief Returns non-zero if player 1 pressed right on the car-select screen. */
int input_p1_nav_right(void);

/** @brief Returns non-zero if player 2 pressed left on the car-select screen. */
int input_p2_nav_left(void);

/** @brief Returns non-zero if player 2 pressed right on the car-select screen. */
int input_p2_nav_right(void);

/** @brief Returns non-zero if the race start was confirmed on the car-select screen. */
int input_car_select_race_pressed(void);

/** @brief Returns non-zero if the cursor is over the race start button on the car-select screen. */
int input_mouse_over_car_select_race_btn(void);

/** @brief Returns non-zero if the race start button was clicked on the car-select screen. */
int input_mouse_car_select_race_pressed(void);

/** @} */

#endif /* __PROJ_INPUT_H */
