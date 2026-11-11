#include <lcom/lcf.h>
#include <stdlib.h>
#include "game.h"
#include "../../controller/input/input.h"
#include "../resources/resources.h"
#include "../../controller/palette/palette.h"
#include "../../view/view.h"
#include "../../view/elements/car/car_view.h"
#include "../../view/elements/obstacle/obstacle_view.h"
#include "../../view/elements/boost/boost_view.h"
#include "../../view/elements/shield/shield_view.h"
#include "../../view/terrain/track/track_view.h"
#include "../terrain/scenery/scenery.h"
#include "../../view/terrain/scenery/scenery_view.h"
#include "../../view/screens/pause/pause_view.h"
#include "../../view/screens/win/win_view.h"
#include "../../view/hud/heart/heart_view.h"
#include "../../view/hud/timer/timer_view.h"
#include "../../view/hud/minimap/minimap_view.h"
#include "../../view/screens/menu/menu_view.h"
#include "../../view/screens/mode_select/mode_select_view.h"
#include "../../view/screens/car_select/car_select_view.h"
#include "../../view/screens/biome_select/biome_select_view.h"
#include "../../view/screens/leaderboard/leaderboard_view.h"
#include "../../view/screens/instructions/instructions_view.h"
#include "../leaderboard/leaderboard.h"

#define CLUSTER_CHANCE     70
#define BOOST_TILES        2
#define BOOST_SPAWN_CHANCE 65
#define SHIELD_SPAWN_CHANCE 20
#define MENU_START        0
#define MENU_INSTRUCTIONS 1
#define MENU_LEADERBOARD  2
#define MENU_EXIT         3
#define MENU_ITEMS        4

static Game game;

static bool position_has_obstacle(int row, int lane) {
    for (int i = 0; i < game.obstacle_count; i++) {
        Obstacle *o = game.obstacles[i];
        if (o && o->base.is_active && o->row == row && o->lane == lane) return true;
    }
    return false;
}

static bool position_has_boost(int row, int lane) {
    for (int i = 0; i < game.boost_count; i++) {
        Boost *b = game.boosts[i];
        if (b && b->base.is_active && b->row == row && b->lane == lane) return true;
    }
    return false;
}

static bool position_has_shield(int row, int lane) {
    for (int i = 0; i < game.shield_count; i++) {
        Shield *s = game.shields[i];
        if (s && s->base.is_active && s->row == row && s->lane == lane) return true;
    }
    return false;
}

static void spawn_boost(int row, int lane_min, int lane_max) {
    if (game.boost_count >= MAX_BOOSTS) return;
    int start = lane_min + rand() % (lane_max - lane_min + 1);
    int lane = -1;
    for (int i = 0; i <= lane_max - lane_min; i++) {
        int candidate = lane_min + (start - lane_min + i) % (lane_max - lane_min + 1);
        if (!position_has_obstacle(row, candidate) && !position_has_shield(row, candidate)) { lane = candidate; break; }
    }
    if (lane == -1) return;
    game.boosts[game.boost_count] = create_boost(row, lane);
    game.boost_count++;
}

static void spawn_shield(int row, int lane_min, int lane_max) {
    if (game.shield_count >= MAX_SHIELDS) return;
    int start = lane_min + rand() % (lane_max - lane_min + 1);
    int lane = -1;
    for (int i = 0; i <= lane_max - lane_min; i++) {
        int candidate = lane_min + (start - lane_min + i) % (lane_max - lane_min + 1);
        if (!position_has_obstacle(row, candidate) && !position_has_boost(row, candidate)) { lane = candidate; break; }
    }
    if (lane == -1) return;
    game.shields[game.shield_count] = create_shield(row, lane);
    game.shield_count++;
}

static void spawn_single(int row, int lane_min, int lane_max) {
    if (game.obstacle_count >= MAX_OBSTACLES) return;
    int start = lane_min + rand() % (lane_max - lane_min + 1);
    int lane = -1;
    for (int i = 0; i <= lane_max - lane_min; i++) {
        int candidate = lane_min + (start - lane_min + i) % (lane_max - lane_min + 1);
        if (!position_has_boost(row, candidate)) { lane = candidate; break; }
    }
    if (lane == -1) return;
    game.obstacles[game.obstacle_count] = create_obstacle(row, lane, OBSTACLE_ROCK);
    game.obstacle_count++;
}

static void spawn_cluster(int base_row, int lane_min, int lane_max) {
    int available = lane_max - lane_min + 1;
    int size = 2 + rand() % 2;

    if (rand() % 2) {
        int start = lane_min + rand() % (available - size + 1);
        for (int i = 0; i < size && game.obstacle_count < MAX_OBSTACLES; i++) {
            if (position_has_boost(base_row, start + i)) continue;
            game.obstacles[game.obstacle_count] = create_obstacle(base_row, start + i, OBSTACLE_ROCK);
            game.obstacle_count++;
        }
    } else {
        int lane = lane_min + rand() % available;
        for (int i = 0; i < size && game.obstacle_count < MAX_OBSTACLES; i++) {
            if (position_has_boost(base_row + i, lane)) continue;
            game.obstacles[game.obstacle_count] = create_obstacle(base_row + i, lane, OBSTACLE_ROCK);
            game.obstacle_count++;
        }
    }
}

static void spawn_banana(int row, int lane_min, int lane_max) {
    if (game.obstacle_count >= MAX_OBSTACLES) return;
    int start = lane_min + rand() % (lane_max - lane_min + 1);
    int lane = -1;
    for (int i = 0; i <= lane_max - lane_min; i++) {
        int candidate = lane_min + (start - lane_min + i) % (lane_max - lane_min + 1);
        if (!position_has_boost(row, candidate) && !position_has_obstacle(row, candidate)) { lane = candidate; break; }
    }
    if (lane == -1) return;
    game.obstacles[game.obstacle_count] = create_obstacle(row, lane, OBSTACLE_BANANA);
    game.obstacle_count++;
}

static void spawn_oil(int row, int lane_min, int lane_max) {
    if (game.obstacle_count >= MAX_OBSTACLES) return;
    int start = lane_min + rand() % (lane_max - lane_min + 1);
    int lane = -1;
    for (int i = 0; i <= lane_max - lane_min; i++) {
        int candidate = lane_min + (start - lane_min + i) % (lane_max - lane_min + 1);
        if (!position_has_boost(row, candidate) && !position_has_obstacle(row, candidate)) { lane = candidate; break; }
    }
    if (lane == -1) return;
    game.obstacles[game.obstacle_count] = create_obstacle(row, lane, OBSTACLE_OIL);
    game.obstacle_count++;
}

/* ── gestão de memória e spawn dinâmico ──────────────────────────── */

#define ENDURANCE_LOOKAHEAD 30

static void game_cleanup_inactive(void) {
    int w = 0;
    for (int i = 0; i < game.obstacle_count; i++) {
        if (game.obstacles[i] && game.obstacles[i]->base.is_active)
            game.obstacles[w++] = game.obstacles[i];
        else { destroy_obstacle(game.obstacles[i]); game.obstacles[i] = NULL; }
    }
    game.obstacle_count = w;
    w = 0;
    for (int i = 0; i < game.boost_count; i++) {
        if (game.boosts[i] && game.boosts[i]->base.is_active)
            game.boosts[w++] = game.boosts[i];
        else { destroy_boost(game.boosts[i]); game.boosts[i] = NULL; }
    }
    game.boost_count = w;
    w = 0;
    for (int i = 0; i < game.shield_count; i++) {
        if (game.shields[i] && game.shields[i]->base.is_active)
            game.shields[w++] = game.shields[i];
        else { destroy_shield(game.shields[i]); game.shields[i] = NULL; }
    }
    game.shield_count = w;
}

static void game_spawn_endurance(void) {
    int target = game.track->scroll_row + TRACK_VISIBLE_ROWS + ENDURANCE_LOOKAHEAD;
    while (game.last_spawn_row < target) {
        int row = game.last_spawn_row;
        bool p1 = game.car1->base.is_active;
        bool p2 = game.car2->base.is_active;

        if (row % 8 == 0) {
            if (p1) { if (rand() % 100 < CLUSTER_CHANCE) spawn_cluster(row, PLAYER1_LANE_START, PLAYER1_LANE_END); else spawn_single(row, PLAYER1_LANE_START, PLAYER1_LANE_END); }
            if (p2) { if (rand() % 100 < CLUSTER_CHANCE) spawn_cluster(row, PLAYER2_LANE_START, PLAYER2_LANE_END); else spawn_single(row, PLAYER2_LANE_START, PLAYER2_LANE_END); }
        }
        if (row % 12 == 0) {
            if (p1 && rand() % 100 < 35) spawn_banana(row, PLAYER1_LANE_START, PLAYER1_LANE_END);
            if (p2 && rand() % 100 < 35) spawn_banana(row, PLAYER2_LANE_START, PLAYER2_LANE_END);
        }
        if (row % 20 == 0) {
            if (p1 && rand() % 100 < SHIELD_SPAWN_CHANCE) spawn_shield(row, PLAYER1_LANE_START, PLAYER1_LANE_END);
            if (p2 && rand() % 100 < SHIELD_SPAWN_CHANCE) spawn_shield(row, PLAYER2_LANE_START, PLAYER2_LANE_END);
        }
        if (row % 15 == 0 && game.track->theme == TRACK_THEME_DESERT) {
            if (p1 && rand() % 100 < 40) spawn_oil(row, PLAYER1_LANE_START, PLAYER1_LANE_END);
            if (p2 && rand() % 100 < 40) spawn_oil(row, PLAYER2_LANE_START, PLAYER2_LANE_END);
        }
        game.last_spawn_row++;
    }
}

/* ── ciclo de vida da sessão ──────────────────────────────────────── */

static void game_var_init(Game *game) {
    game->track = create_track(game->selected_theme);
    if (game->mode_selection == 1) game->track->infinite = true;
    game->car1 = create_car(2, PLAYER1_LANE_START, PLAYER1_LANE_END, CAR_WIDTH, CAR_HEIGHT);
    game->car1->player = 1;
    game->car2 = create_car(7, PLAYER2_LANE_START, PLAYER2_LANE_END, CAR_WIDTH, CAR_HEIGHT);
    game->car2->player = 2;
    game->scenery = scenery_create(game->selected_theme);
    game->winner = 0;
    game->pause_selected = 0;
    game->win_selected = 0;
    game->obstacle_count = 0;
    game->boost_count = 0;
    game->shield_count = 0;
    game->elapsed_ticks = 0;
    game->last_spawn_row  = 20;
    game->car1_death_tick = 0;
    game->car2_death_tick = 0;
}
void game_create(Game *game) {
    game_var_init(game);

    if (game->mode_selection == 0) {
        /* Race mode: spawn estático para todo o track */
        for (int row = 20; row < TRACK_TOTAL_ROWS - 10 && game->boost_count < MAX_BOOSTS; row += 10) {
            if (rand() % 100 < BOOST_SPAWN_CHANCE)
                spawn_boost(row, PLAYER1_LANE_START, PLAYER1_LANE_END);
            if (rand() % 100 < BOOST_SPAWN_CHANCE)
                spawn_boost(row, PLAYER2_LANE_START, PLAYER2_LANE_END);
        }

        for (int row = 20; row < TRACK_TOTAL_ROWS - 10 && game->obstacle_count < MAX_OBSTACLES - 6; row += 8) {
            if (rand() % 100 < CLUSTER_CHANCE)
                spawn_cluster(row, PLAYER1_LANE_START, PLAYER1_LANE_END);
            else
                spawn_single(row, PLAYER1_LANE_START, PLAYER1_LANE_END);

            if (rand() % 100 < CLUSTER_CHANCE)
                spawn_cluster(row + 4, PLAYER2_LANE_START, PLAYER2_LANE_END);
            else
                spawn_single(row + 4, PLAYER2_LANE_START, PLAYER2_LANE_END);
        }

        for (int row = 20; row < TRACK_TOTAL_ROWS - 10 && game->obstacle_count < MAX_OBSTACLES; row += 12) {
            if (rand() % 100 < 35)
                spawn_banana(row, PLAYER1_LANE_START, PLAYER1_LANE_END);
            if (rand() % 100 < 35)
                spawn_banana(row + 6, PLAYER2_LANE_START, PLAYER2_LANE_END);
        }

        if (game->track->theme == TRACK_THEME_DESERT) {
            for (int row = 20; row < TRACK_TOTAL_ROWS - 10 && game->obstacle_count < MAX_OBSTACLES; row += 15) {
                if (rand() % 100 < 40)
                    spawn_oil(row, PLAYER1_LANE_START, PLAYER1_LANE_END);
                if (rand() % 100 < 40)
                    spawn_oil(row + 7, PLAYER2_LANE_START, PLAYER2_LANE_END);
            }
        }

        for (int row = 25; row < TRACK_TOTAL_ROWS - 10 && game->shield_count < MAX_SHIELDS; row += 20) {
            if (rand() % 100 < SHIELD_SPAWN_CHANCE)
                spawn_shield(row, PLAYER1_LANE_START, PLAYER1_LANE_END);
            if (rand() % 100 < SHIELD_SPAWN_CHANCE)
                spawn_shield(row + 10, PLAYER2_LANE_START, PLAYER2_LANE_END);
        }
    } else {
        /* Endurance mode: semear janela inicial; spawn dinâmico trata do resto */
        game_spawn_endurance();
    }

    game->state = GAMEPLAY;
}

void game_reset(Game *game) {
    if (game->track) {
        destroy_track(game->track);
        game->track = NULL;
    }
    if (game->car1) {
        destroy_car(game->car1);
        game->car1 = NULL;
    }
    if (game->car2) {
        destroy_car(game->car2);
        game->car2 = NULL;
    }
    if (game->scenery) {
        scenery_destroy(game->scenery);
        game->scenery = NULL;
    }
    for (int i = 0; i < game->obstacle_count; i++) {
        if (game->obstacles[i]) {
            destroy_obstacle(game->obstacles[i]);
            game->obstacles[i] = NULL;
        }
    }
    game->obstacle_count = 0;
    for (int i = 0; i < game->boost_count; i++) {
        if (game->boosts[i]) {
            destroy_boost(game->boosts[i]);
            game->boosts[i] = NULL;
        }
    }
    game->boost_count = 0;
    for (int i = 0; i < game->shield_count; i++) {
        if (game->shields[i]) {
            destroy_shield(game->shields[i]);
            game->shields[i] = NULL;
        }
    }
    game->shield_count = 0;
    game_create(game);
}

/* ── input / update / render ──────────────────────────────────────── */

static void game_process_input(void) {
    switch (game.state) {
        case MAIN_MENU:
            if (input_esc_pressed()) {    game.state = EXIT; break; }
            if (input_menu_nav_up())
                game.menu_selection = (game.menu_selection + MENU_ITEMS - 1) % MENU_ITEMS;
            if (input_menu_nav_down())
                game.menu_selection = (game.menu_selection + 1) % MENU_ITEMS;
            if (input_mouse_over_start())        game.menu_selection = MENU_START;
            if (input_mouse_over_instructions()) game.menu_selection = MENU_INSTRUCTIONS;
            if (input_mouse_over_leaderboard())  game.menu_selection = MENU_LEADERBOARD;
            if (input_mouse_over_exit())         game.menu_selection = MENU_EXIT;

            if (input_keyboard_start_pressed()) {
                if      (game.menu_selection == MENU_START)        game.state = CAR_SELECT;
                else if (game.menu_selection == MENU_INSTRUCTIONS) game.state = INSTRUCTIONS;
                else if (game.menu_selection == MENU_LEADERBOARD)  game.state = LEADERBOARD;
                else if (game.menu_selection == MENU_EXIT)         game.state = EXIT;
            }
            if (input_mouse_start_pressed())        game.state = CAR_SELECT;
            if (input_mouse_instructions_pressed()) game.state = INSTRUCTIONS;
            if (input_mouse_leaderboard_pressed())  game.state = LEADERBOARD;
            if (input_mouse_exit_pressed())         game.state = EXIT;
            break;
        case CAR_SELECT: {
            int n = resources_get_car_format_count();
            if (n < 1) n = 1;
            if (input_esc_pressed()) { game.state = MAIN_MENU; break; }
            if (input_p1_nav_left())  game.car1_format = (game.car1_format - 1 + n) % n;
            if (input_p1_nav_right()) game.car1_format = (game.car1_format + 1)     % n;
            if (input_p2_nav_left())  game.car2_format = (game.car2_format - 1 + n) % n;
            if (input_p2_nav_right()) game.car2_format = (game.car2_format + 1)     % n;
            if (input_car_select_race_pressed() || input_mouse_car_select_race_pressed()) {
                resources_apply_car_format(game.car1_format, game.car2_format);
                game.state = BIOME_SELECT;
            }
            break;
        }
        case BIOME_SELECT:
            if (input_esc_pressed()) { game.state = CAR_SELECT; break; }
            if (input_biome_nav_left() || input_mouse_biome_arrow_left())
                game.selected_theme = (TrackTheme)((game.selected_theme + TRACK_THEME_COUNT - 1) % TRACK_THEME_COUNT);
            if (input_biome_nav_right() || input_mouse_biome_arrow_right())
                game.selected_theme = (TrackTheme)((game.selected_theme + 1) % TRACK_THEME_COUNT);
            if (input_biome_select_pressed() || input_mouse_biome_select_pressed())
                game.state = MODE_SELECT;
            break;
        case MODE_SELECT:
            if (input_esc_pressed()) { game.mode_selection = 0; game.state = BIOME_SELECT; break; }
            if (input_mode_nav_left())               game.mode_selection = 0;
            if (input_mode_nav_right())              game.mode_selection = 1;
            if (input_mouse_over_race_card())        game.mode_selection = 0;
            if (input_mouse_over_endurance_card())   game.mode_selection = 1;
            if (input_mouse_race_card_pressed())     { game.mode_selection = 0; game_reset(&game); }
            else if (input_mouse_endurance_card_pressed()) { game.mode_selection = 1; game_reset(&game); }
            else if (input_keyboard_confirm_pressed()) game_reset(&game);
            break;
        case GAMEPLAY:
            if (input_keyboard_pause_pressed()) {
                game.pause_selected = 0;
                game.state = PAUSE;
            }
            if (input_keyboard_car_left_pressed()  || input_keyboard_car1_left_pressed())  car_move_lane(game.car1, -1);
            if (input_keyboard_car_right_pressed() || input_keyboard_car1_right_pressed()) car_move_lane(game.car1, +1);
            if (input_mouse_car2_left())  car_move_lane(game.car2, -1);
            if (input_mouse_car2_right()) car_move_lane(game.car2, +1);
            break;
        case PAUSE:
            if (input_mouse_over_pause_resume()) game.pause_selected = 0;
            if (input_mouse_over_pause_quit())   game.pause_selected = 1;
            if (input_keyboard_pause_pressed() || input_mouse_pause_resume_pressed()) {
                game.state = GAMEPLAY;
            } else if (input_mouse_pause_quit_pressed()) {
                game.menu_selection = 0;
                game.state = MAIN_MENU;
            } else if (input_keyboard_up_pressed() || input_keyboard_down_pressed()) {
                game.pause_selected = 1 - game.pause_selected;
            } else if (input_keyboard_confirm_pressed()) {
                if (game.pause_selected == 0)
                    game.state = GAMEPLAY;
                else {
                    game.menu_selection = 0;
                    game.state = MAIN_MENU;
                }
            }
            break;
        case GAME_OVER:
            if (input_mouse_over_win_play_again()) game.win_selected = 0;
            if (input_mouse_over_win_menu())       game.win_selected = 1;
            if (input_menu_nav_left())  game.win_selected = 0;
            if (input_menu_nav_right()) game.win_selected = 1;
            if (input_keyboard_confirm_pressed()) {
                if (game.win_selected == 0) game_reset(&game);
                else { game.menu_selection = 0; game.state = MAIN_MENU; }
            }
            if (input_mouse_win_play_again_pressed()) game_reset(&game);
            if (input_mouse_win_menu_pressed()) { game.menu_selection = 0; game.state = MAIN_MENU; }
            if (input_gameover_menu_pressed())  { game.menu_selection = 0; game.state = MAIN_MENU; }
            break;
        case INSTRUCTIONS:
            if (input_esc_pressed() || input_keyboard_confirm_pressed())
                game.state = MAIN_MENU;
            break;
        case LEADERBOARD:
            if (input_leaderboard_back_pressed()) game.state = MAIN_MENU;
            break;
        case EXIT:
            break;
    }
    input_flush();
}

static void apply_boost_movement(Car* car, float boost_speed) {
    if (car->boost_remaining <= 0.0f) return;
    float step = car->boost_remaining < boost_speed ? car->boost_remaining : boost_speed;
    car->base.y -= (double)step;
    if (car->base.y < 0.0) car->base.y = 0.0;
    car->boost_remaining -= step;
}

static void game_update(void) {
    input_tick_inverted();
    track_update(game.track);
    scenery_update(game.scenery, game.track);

    game_cleanup_inactive();

    if (game.mode_selection == 1) {
        float exit_speed = game.track->scroll_speed + 6.0f;
        if (game.car1->exploding) {
            game.car1->base.y += exit_speed;
            if (game.car1->base.y >= (TRACK_VISIBLE_ROWS + 1) * TRACK_TILE_HEIGHT) {
                game.car1->base.is_active = false;
                game.car1->exploding      = false;
            }
        }
        if (game.car2->exploding) {
            game.car2->base.y += exit_speed;
            if (game.car2->base.y >= (TRACK_VISIBLE_ROWS + 1) * TRACK_TILE_HEIGHT) {
                game.car2->base.is_active = false;
                game.car2->exploding      = false;
            }
        }
        game_spawn_endurance();
    }

    float boost_speed = game.track->scroll_speed * 3.0f;
    apply_boost_movement(game.car1, boost_speed);
    apply_boost_movement(game.car2, boost_speed);

    for (int i = 0; i < game.obstacle_count; i++) {
        if (game.obstacles[i] != NULL)
            obstacle_update(game.obstacles[i], game.track->scroll_row, game.track->scroll_offset);
    }
    for (int i = 0; i < game.boost_count; i++) {
        if (game.boosts[i] != NULL)
            boost_update(game.boosts[i], game.track->scroll_row, game.track->scroll_offset);
    }
    for (int i = 0; i < game.shield_count; i++) {
        if (game.shields[i] != NULL)
            shield_update(game.shields[i], game.track->scroll_row, game.track->scroll_offset);
    }

    if (game.car1->shield_ticks > 0) game.car1->shield_ticks--;
    if (game.car2->shield_ticks > 0) game.car2->shield_ticks--;
}

static void game_process_collisions(void) {
    bool c1_active_before = game.car1->base.is_active && !game.car1->exploding;
    bool c2_active_before = game.car2->base.is_active && !game.car2->exploding;

    for (int i = 0; i < game.obstacle_count; i++) {
        Obstacle *obs = game.obstacles[i];
        if (obs == NULL || !obs->base.is_active) continue;

        if (c1_active_before && obstacle_collides_with_car(obs, game.car1)) {
            if (obs->type == OBSTACLE_BANANA || obs->type == OBSTACLE_OIL) {
                if (game.car1->shield_ticks > 0)
                    game.car1->shield_ticks = 0;
                else {
                    car_banana_slip(game.car1);
                    input_set_car1_inverted(180);
                }
            } else {
                car_take_damage(game.car1);
            }
            obs->base.is_active = false;
        }
        if (c2_active_before && obstacle_collides_with_car(obs, game.car2)) {
            if (obs->type == OBSTACLE_BANANA || obs->type == OBSTACLE_OIL) {
                if (game.car2->shield_ticks > 0)
                    game.car2->shield_ticks = 0;
                else {
                    car_banana_slip(game.car2);
                    input_set_car2_inverted(180);
                }
            } else {
                car_take_damage(game.car2);
            }
            obs->base.is_active = false;
        }
    }

    for (int i = 0; i < game.boost_count; i++) {
        Boost *boost = game.boosts[i];
        if (boost == NULL || !boost->base.is_active) continue;

        if (c1_active_before && boost_collides_with_car(boost, game.car1)) {
            car_apply_boost(game.car1, BOOST_TILES);
            boost->base.is_active = false;
        } else if (c2_active_before && boost_collides_with_car(boost, game.car2)) {
            car_apply_boost(game.car2, BOOST_TILES);
            boost->base.is_active = false;
        }
    }

    for (int i = 0; i < game.shield_count; i++) {
        Shield *shield = game.shields[i];
        if (shield == NULL || !shield->base.is_active) continue;

        if (c1_active_before && shield_collides_with_car(shield, game.car1)) {
            car_apply_shield(game.car1, SHIELD_DURATION_TICKS);
            shield->base.is_active = false;
        } else if (c2_active_before && shield_collides_with_car(shield, game.car2)) {
            car_apply_shield(game.car2, SHIELD_DURATION_TICKS);
            shield->base.is_active = false;
        }
    }

    /* Endurance: se um carro acabou de morrer nesta frame, inicia animação de saída */
    if (game.mode_selection == 1) {
        if (c1_active_before && !game.car1->base.is_active) {
            game.car1->base.is_active = true;
            game.car1->exploding      = true;
            game.car1_death_tick      = game.elapsed_ticks;
        }
        if (c2_active_before && !game.car2->base.is_active) {
            game.car2->base.is_active = true;
            game.car2->exploding      = true;
            game.car2_death_tick      = game.elapsed_ticks;
        }
    }
}

static bool car_at_finish_line(const Car *car) {
    float finish_y = (float)((2 * CAR_SCREEN_ROW
                              - (TRACK_TOTAL_ROWS - 1 - game.track->scroll_row))
                             * TRACK_TILE_HEIGHT)
                    + game.track->scroll_offset;
    return (float)car->base.y              <= finish_y + TRACK_TILE_HEIGHT
        && (float)(car->base.y + CAR_HEIGHT) > finish_y;
}

static bool game_is_over(void) {
    if (game.mode_selection == 0) {
        /* Race mode */
        if (!game.car1->base.is_active) { game.winner = 2; return true; }
        if (!game.car2->base.is_active) { game.winner = 1; return true; }
        bool c1_fin = car_at_finish_line(game.car1);
        bool c2_fin = car_at_finish_line(game.car2);
        if (c1_fin || c2_fin) {
            if (c1_fin && c2_fin)
                game.winner = 0;
            else
                game.winner = c1_fin ? 1 : 2;
            return true;
        }
    } else {
        /* Endurance mode: ambos os carros têm de ser destruídos */
        if (!game.car1->base.is_active && !game.car2->base.is_active) {
            game.winner = (game.car1_death_tick >= game.car2_death_tick) ? 1 : 2;
            return true;
        }
    }
    return false;
}

#include "config.h"

static void game_render_track_scene(void) {
    track_view_draw(game.track);
    scenery_view_draw(game.scenery, game.track, game.track->theme);
    car_view_draw(game.car1, game.track->theme);
    car_view_draw(game.car2, game.track->theme);
    shield_aura_draw(game.car1);
    shield_aura_draw(game.car2);
    for (int i = 0; i < game.obstacle_count; i++) {
        if (obstacle_is_visible(game.obstacles[i]))
            obstacle_view_draw(game.obstacles[i], game.track->theme);
    }
    for (int i = 0; i < game.boost_count; i++) {
        if (boost_is_visible(game.boosts[i]))
            boost_view_draw(game.boosts[i]);
    }
    for (int i = 0; i < game.shield_count; i++) {
        if (shield_is_visible(game.shields[i]))
            shield_view_draw(game.shields[i]);
    }
    timer_view_draw(game.elapsed_ticks);
    heart_view_draw(game.car1, game.car2,
                    input_get_car1_inverted_ticks(), input_get_car2_inverted_ticks());
    if (game.mode_selection == 0)
        minimap_view_draw(game.car1, game.car2, game.track);
}

static void game_render(void) {
    switch (game.state) {
        case GAME_OVER:
            draw_clear(PAL_BLACK);
            win_view_draw(game.winner, game.win_selected);
            copy_buffer_to_video();
            return;
        default:
            break;
    }

    draw_clear(PAL_BLACK);

    switch (game.state) {
        case LEADERBOARD:
            leaderboard_view_draw();
            copy_buffer_to_video();
            return;
        case INSTRUCTIONS:
            instructions_view_draw();
            break;
        case MAIN_MENU:
            menu_view_draw(game.menu_selection);
            break;
        case CAR_SELECT:
            car_select_view_draw(
                game.car1_format, game.car2_format,
                resources_get_car_format_count()
            );
            break;
        case BIOME_SELECT:
            biome_select_view_draw(game.selected_theme);
            break;
        case MODE_SELECT:
            mode_select_view_draw(game.mode_selection);
            break;
        case GAMEPLAY:
            game_render_track_scene();
            break;
        case GAME_OVER:
            break;
        case PAUSE:
            game_render_track_scene();
            pause_view_draw(game.pause_selected);
            draw_sprite(resources_get_cursor_sprite(), input_cursor_x(), input_cursor_y());
            break;
        case EXIT:
            break;
    }

    copy_buffer_to_video();
}

void game_init(void) {
    resources_destroy();
    resources_load();
    leaderboard_init();
    leaderboard_view_init();
    input_init_cursor(SCREEN_W, SCREEN_H);
    game.state = MAIN_MENU;
    game.winner = 0;
    game.pause_selected = 0;
    game.win_selected = 0;
    game.menu_selection = 0;
    game.selected_theme = TRACK_THEME_CITY;
    game.mode_selection = 0;
    game.track = NULL;
    game.car1 = NULL;
    game.car2 = NULL;
    game.scenery = NULL;
    game.obstacle_count = 0;
    game.boost_count = 0;
    game.shield_count = 0;
    game.car1_format = 0;
    game.car2_format = 0;
}

void game_cleanup(void) {
    game_reset(&game);
    resources_destroy();
}

GameState game_get_state(void) {
    return game.state;
}

void game_set_state(GameState new_state) {
    game.state = new_state;
}

const Game *game_get(void) {
    return &game;
}

void game_tick(void) {
    game_process_input();

    switch (game.state) {
        case GAMEPLAY:
            game.elapsed_ticks++;
            game_update();
            game_process_collisions();
            if (game_is_over()) {
                if (game.mode_selection == 1) {
                    int h, m, s;
                    leaderboard_read_rtc(&h, &m, &s);
                    const char *winner_name = (game.winner == 1) ? "BLUE" : (game.winner == 2) ? "RED" : "DRAW";
                    leaderboard_add(winner_name,
                                    (int)(game.elapsed_ticks / 60),
                                    h, m, s);
                }
                game.state = GAME_OVER;
            }
            break;
        case CAR_SELECT:
        case BIOME_SELECT:
            break;
        case MAIN_MENU:
        case INSTRUCTIONS:
        case MODE_SELECT:
        case PAUSE:
        case GAME_OVER:
        case LEADERBOARD:
        case EXIT:
            break;
    }

    game_render();
}
