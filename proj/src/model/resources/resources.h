/**
 * @file resources.h
 * @brief Global sprite cache — loads and owns all game assets at startup.
 */

#ifndef __PROJ_RESOURCES_H
#define __PROJ_RESOURCES_H

#include "../common/sprite/sprite.h"
#include "../terrain/track/track.h"
#include "../elements/car/car.h"

#define CAR_FORMAT_MAX 8  /**< Maximum number of selectable car formats. */

/**
 * @brief Lateral ground tile variant indices (per theme, up to GROUND_TILE_COUNT).
 */
typedef enum {
    GROUND_TILE_SOIL   = 0, /**< Soft soil / grass — trees may spawn here. */
    GROUND_TILE_ROCKS  = 1, /**< Rocky ground — trees may spawn here. */
    GROUND_TILE_COBBLE = 2, /**< Hard cobblestone — no trees. */
    GROUND_TILE_BLOCK  = 3, /**< Decorative paved block — no trees. */
    GROUND_TILE_COUNT       /**< Total number of lateral tile variants. */
} GroundTileVariant;

/**
 * @brief Container for every sprite used by the game.
 *
 * Owned exclusively by the resources module; all other modules hold
 * non-owning pointers obtained through the getter functions below.
 */
typedef struct {
    Sprite *car_sprites[CAR_PLAYER_COUNT][CAR_STATE_COUNT]; /**< [player][CarState] */
    Sprite *obstacle_sprites[TRACK_THEME_COUNT]; /**< [TrackTheme] main obstacle per biome. */
    Sprite *city_obstacle_sprites[16]; /**< 16 random city obstacle item sprites. */
    Sprite *forest_obstacle_sprites[4]; /**< 4 colorful forest obstacle sprites. */
    Sprite *boost_sprite;             /**< Boost pickup (legacy). */
    Sprite *city_boost_sprites[3];    /**< 3 random city boost sprites. */
    Sprite *tile_sprites[TRACK_THEME_COUNT][4];    /**< [TrackTheme][TileType] road tiles. */
    Sprite *ground_tiles[TRACK_THEME_COUNT][GROUND_TILE_COUNT]; /**< [TrackTheme][GroundTileVariant] */
    Sprite *wall_sprites[TRACK_THEME_COUNT];       /**< [TrackTheme] road-edge wall delimiter. */
    Sprite *scenery_sprites[TRACK_THEME_COUNT];    /**< [TrackTheme] lateral scenery per biome. */
    Sprite *divider_sprite;           /**< Lane divider line. */
    Sprite *haybale_sprite;           /**< Hay bale — desert obstacle. */
    Sprite *menu_title;               /**< Main menu title graphic. */
    Sprite *menu_start_btn;           /**< START button. */
    Sprite *menu_instructions_btn;   /**< INSTRUCTIONS button. */
    Sprite *menu_leaderboard_btn;     /**< LEADERBOARD button. */
    Sprite *menu_exit_btn;            /**< EXIT button. */
    Sprite *pause_panel;              /**< Pause overlay background panel. */
    Sprite *pause_resume_btn[2];      /**< [0]=normal  [1]=highlighted. */
    Sprite *pause_quit_btn[2];        /**< [0]=normal  [1]=highlighted. */
    Sprite *cursor_sprite;            /**< Mouse cursor. */
    Sprite *banana_frames[16];        /**< Banana animation frames (16 tiles, row-major). */
    Sprite *heart_sprite;             /**< Heart icon for life counter. */
    Sprite *digit_sprites[10];        /**< Digit glyphs 0-9 for the timer. */
    Sprite *colon_sprite;             /**< Colon ':' glyph for the timer. */
    Sprite *fence_sprite;             /**< Fence scenery element. */
    Sprite *oil_puddle_sprite;        /**< Oil puddle obstacle. */
    Sprite *sand_pebbles_sprite;      /**< Sand pebbles scenery element. */
    Sprite *mode_select_title;        /**< Mode-selection screen title. */
    Sprite *mode_race_card;           /**< RACE mode card graphic. */
    Sprite *mode_endurance_card;      /**< ENDURANCE mode card graphic. */
    Sprite *mode_race_label;          /**< RACE mode label. */
    Sprite *mode_endurance_label;     /**< ENDURANCE mode label. */
    Sprite *car_format_sprites[CAR_FORMAT_MAX][CAR_PLAYER_COUNT][CAR_STATE_COUNT]; /**< [fmt][player][CarState] */
    int     car_format_count;         /**< Number of loaded car formats. */
    Sprite *win_img[2];               /**< [0]=blue_wins  [1]=red_wins. */
    Sprite *win_play_again_btn;       /**< PLAY AGAIN button. */
    Sprite *win_menu_btn;             /**< MENU button. */
    Sprite *shield_sprite;            /**< Shield pickup icon. */
    Sprite *shield_aura_sprite;       /**< Yellow aura overlay while shielded. */
    Sprite *road_detail_sprite;        /**< City road detail overlay (road.xpm). */
    Sprite *inner_road_left_sprite;    /**< City inner road tile — lane 4 (left of divider). */
    Sprite *inner_road_right_sprite;   /**< City inner road tile — lane 5 (right of divider). */
    Sprite *biome_select_title;       /**< Biome selector screen title. */
    Sprite *biome_labels[TRACK_THEME_COUNT]; /**< [TrackTheme] biome name label per biome. */
} Resources;

/**
 * @brief Loads all game sprites from their XPM sources into the global cache.
 * @return 0 on success, non-zero on the first allocation failure.
 */
int  resources_load(void);

/**
 * @brief Frees every sprite in the global resource cache.
 */
void resources_destroy(void);

/**
 * @brief Returns the sprite for a car in a given visual state.
 * @param player 0 for player 1, 1 for player 2.
 * @param state  CarState index (0–3).
 * @return Non-owning pointer to the sprite.
 */
Sprite* resources_get_car_sprite(int player, int state);

/**
 * @brief Returns the rock obstacle sprite for the city theme.
 * @return Non-owning pointer to the sprite.
 */
Sprite* resources_get_obstacle_sprite(void);

/**
 * @brief Returns the boost pickup sprite.
 * @return Non-owning pointer to the sprite.
 */
Sprite* resources_get_boost_sprite(void);

/**
 * @brief Returns a city-theme road tile sprite.
 * @param type TileType index (0–3).
 * @return Non-owning pointer to the sprite.
 */
Sprite* resources_get_tile_sprite(int type);

/**
 * @brief Returns a lateral ground tile for the given theme and variant.
 * @param theme   TrackTheme value.
 * @param variant GroundTileVariant index (0 = SOIL, …).
 * @return Non-owning pointer; NULL if the variant is unused for that theme.
 */
Sprite* resources_get_ground_tile(int theme, int variant);

/**
 * @brief Returns the SOIL (variant 0) lateral ground sprite for the given theme.
 * @param theme TrackTheme value.
 */
Sprite* resources_get_ground_sprite(int theme);

/**
 * @brief Returns the lateral scenery sprite for the given theme.
 * @param theme TrackTheme value.
 * @return Tree sprite for city/forest; cactus sprite for desert.
 */
Sprite* resources_get_scenery_sprite(int theme);

/**
 * @brief Returns a road tile sprite for the given tile type and theme.
 * @param type  TileType index.
 * @param theme TrackTheme value.
 * @return Non-owning pointer to the sprite.
 */
Sprite* resources_get_tile_sprite_themed(int type, int theme);

/**
 * @brief Returns the lane-divider sprite.
 * @return Non-owning pointer to the sprite.
 */
Sprite* resources_get_divider_sprite(void);

/**
 * @brief Returns the main menu title sprite.
 * @return Non-owning pointer to the sprite.
 */
Sprite* resources_get_menu_title(void);

/**
 * @brief Returns the START button sprite.
 * @return Non-owning pointer to the sprite.
 */
Sprite* resources_get_menu_start_btn(void);

/**
 * @brief Returns the LEADERBOARD button sprite.
 * @return Non-owning pointer to the sprite.
 */
Sprite* resources_get_menu_leaderboard_btn(void);

/**
 * @brief Returns the EXIT button sprite.
 * @return Non-owning pointer to the sprite.
 */
Sprite* resources_get_menu_exit_btn(void);

/**
 * @brief Returns the pause overlay panel sprite.
 * @return Non-owning pointer to the sprite.
 */
Sprite* resources_get_pause_panel(void);

/**
 * @brief Returns the RESUME button sprite.
 * @param selected 1 if the button is currently highlighted, 0 otherwise.
 * @return Non-owning pointer to the sprite.
 */
Sprite* resources_get_pause_resume_btn(int selected);

/**
 * @brief Returns the QUIT button sprite.
 * @param selected 1 if the button is currently highlighted, 0 otherwise.
 * @return Non-owning pointer to the sprite.
 */
Sprite* resources_get_pause_quit_btn(int selected);

/**
 * @brief Returns the mouse cursor sprite.
 * @return Non-owning pointer to the sprite.
 */
Sprite* resources_get_cursor_sprite(void);

/**
 * @brief Returns the banana animation frame for the given tick.
 * @param tick Game tick (use game_get()->elapsed_ticks).
 * @return Non-owning pointer to the current frame sprite.
 */
Sprite* resources_get_banana_sprite(uint32_t tick);

/**
 * @brief Returns the heart (life counter) sprite.
 * @return Non-owning pointer to the sprite.
 */
Sprite* resources_get_heart_sprite(void);

/**
 * @brief Returns the digit sprite for a numeric glyph.
 * @param digit Value in [0, 9].
 * @return Non-owning pointer to the sprite.
 */
Sprite* resources_get_digit_sprite(int digit);

/**
 * @brief Returns the colon ':' sprite for the timer display.
 * @return Non-owning pointer to the sprite.
 */
Sprite* resources_get_colon_sprite(void);

/**
 * @brief Returns the obstacle sprite for a given track theme.
 * @param theme TrackTheme value.
 * @return Rock sprite for city/forest; barrel sprite for desert.
 */
Sprite* resources_get_obstacle_sprite_themed(int theme);

/**
 * @brief Returns the fence scenery sprite (city/forest theme).
 * @return Non-owning pointer to the sprite.
 */
Sprite* resources_get_fence_sprite(void);

/**
 * @brief Returns the oil puddle obstacle sprite.
 * @return Non-owning pointer to the sprite.
 */
Sprite* resources_get_oil_puddle_sprite(void);

/**
 * @brief Returns the sand pebbles scenery sprite (desert theme).
 * @return Non-owning pointer to the sprite.
 */
Sprite* resources_get_sand_pebbles_sprite(void);

/**
 * @brief Returns the mode-selection screen title sprite.
 * @return Non-owning pointer to the sprite.
 */
Sprite* resources_get_mode_select_title(void);

/**
 * @brief Returns the RACE mode card sprite.
 * @return Non-owning pointer to the sprite.
 */
Sprite* resources_get_mode_race_card(void);

/**
 * @brief Returns the ENDURANCE mode card sprite.
 * @return Non-owning pointer to the sprite.
 */
Sprite* resources_get_mode_endurance_card(void);

/**
 * @brief Returns the RACE mode label sprite.
 * @return Non-owning pointer to the sprite.
 */
Sprite* resources_get_mode_race_label(void);

/**
 * @brief Returns the ENDURANCE mode label sprite.
 * @return Non-owning pointer to the sprite.
 */
Sprite* resources_get_mode_endurance_label(void);
/**
 * @brief Returns the number of available car formats (skins).
 * @return Number of formats loaded (0..CAR_FORMAT_MAX).
 */
int     resources_get_car_format_count(void);

/**
 * @brief Returns the preview sprite for a car format on the car-selection screen.
 * @param fmt    Format index (0..car_format_count-1).
 * @param player 0 for player 1, 1 for player 2.
 * @return Non-owning pointer to the sprite.
 */
Sprite* resources_get_car_format_preview(int fmt, int player);

/**
 * @brief Applies the chosen car formats to the active car sprites.
 *
 * Swaps the car sprite pointers so that car_view_draw uses the selected skins.
 * @param fmt1 Format index chosen by player 1.
 * @param fmt2 Format index chosen by player 2.
 */
void    resources_apply_car_format(int fmt1, int fmt2);

/**
 * @brief Returns the INSTRUCTIONS button sprite for the main menu.
 * @return Non-owning pointer to the sprite.
 */
Sprite* resources_get_menu_instructions_btn(void);

/**
 * @brief Returns the winner announcement image.
 * @param winner 0 = blue (player 1) wins, 1 = red (player 2) wins.
 * @return Non-owning pointer to the sprite.
 */
Sprite* resources_get_win_img(int winner);

/**
 * @brief Returns the PLAY AGAIN button sprite on the win screen.
 * @return Non-owning pointer to the sprite.
 */
Sprite* resources_get_win_play_again_btn(void);

/**
 * @brief Returns the MENU button sprite on the win screen.
 * @return Non-owning pointer to the sprite.
 */
Sprite* resources_get_win_menu_btn(void);

/**
 * @brief Returns one of the 16 city obstacle sprites.
 * @param idx Sprite index in [0, 15].
 * @return Non-owning pointer to the sprite.
 */
Sprite* resources_get_city_obstacle_sprite(int idx);

/**
 * @brief Returns one of the 3 city boost sprites.
 * @param idx Sprite index in [0, 2].
 * @return Non-owning pointer to the sprite.
 */
Sprite* resources_get_city_boost_sprite(int idx);

/**
 * @brief Returns the shield pickup icon sprite.
 * @return Non-owning pointer to the sprite.
 */
Sprite* resources_get_shield_sprite(void);

/**
 * @brief Returns the shield aura overlay sprite (drawn over a shielded car).
 * @return Non-owning pointer to the sprite.
 */
Sprite* resources_get_shield_aura_sprite(void);

/**
 * @brief Returns the city road detail overlay sprite (road.xpm).
 * @return Non-owning pointer to the sprite.
 */
Sprite* resources_get_road_detail_sprite(void);

/**
 * @brief Returns the city inner road tile for lane 4 (left of the centre divider).
 * @return Non-owning pointer to the sprite.
 */
Sprite* resources_get_inner_road_left_sprite(void);

/**
 * @brief Returns the city inner road tile for lane 5 (right of the centre divider).
 * @return Non-owning pointer to the sprite.
 */
Sprite* resources_get_inner_road_right_sprite(void);

/**
 * @brief Returns one of the 4 forest obstacle sprites.
 * @param idx Sprite index in [0, 3].
 * @return Non-owning pointer to the sprite.
 */
Sprite* resources_get_forest_obstacle_sprite(int idx);

/**
 * @brief Returns the biome selector screen title sprite.
 * @return Non-owning pointer; NULL until the XPM is created and loaded.
 */
Sprite* resources_get_biome_select_title(void);

/**
 * @brief Returns the biome name label sprite for a given theme.
 * @param theme TrackTheme value (0=city, 1=desert, 2=forest).
 * @return Non-owning pointer; NULL until the XPM is created and loaded.
 */
Sprite* resources_get_biome_label(int theme);
/**
 * @brief Returns the road-edge wall delimiter sprite for the given theme.
 * @param theme TrackTheme value.
 * @return Non-owning pointer to the sprite.
 */
Sprite* resources_get_wall_sprite(int theme);

#endif /* __PROJ_RESOURCES_H */
