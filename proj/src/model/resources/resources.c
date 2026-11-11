#include <lcom/lcf.h>
#include "resources.h"
#include "../elements/car/car.h"
#include "../terrain/track/track.h"
#include <stdlib.h>

/* ── city obstacles ── */
#include "../../assets/xpm/biomes/city/obstacles/item_1_1.xpm"
#include "../../assets/xpm/biomes/city/obstacles/item_1_2.xpm"
#include "../../assets/xpm/biomes/city/obstacles/item_1_3.xpm"
#include "../../assets/xpm/biomes/city/obstacles/item_1_4.xpm"
#include "../../assets/xpm/biomes/city/obstacles/item_2_1.xpm"
#include "../../assets/xpm/biomes/city/obstacles/item_2_2.xpm"
#include "../../assets/xpm/biomes/city/obstacles/item_2_3.xpm"
#include "../../assets/xpm/biomes/city/obstacles/item_2_4.xpm"
#include "../../assets/xpm/biomes/city/obstacles/item_3_1.xpm"
#include "../../assets/xpm/biomes/city/obstacles/item_3_2.xpm"
#include "../../assets/xpm/biomes/city/obstacles/item_3_3.xpm"
#include "../../assets/xpm/biomes/city/obstacles/item_3_4.xpm"
#include "../../assets/xpm/biomes/city/obstacles/item_4_1.xpm"
#include "../../assets/xpm/biomes/city/obstacles/item_4_2.xpm"
#include "../../assets/xpm/biomes/city/obstacles/item_4_3.xpm"
#include "../../assets/xpm/biomes/city/obstacles/item_4_4.xpm"

/* ── city ── */
#include "../../assets/xpm/biomes/city/tiles/tile_road.xpm"
#include "../../assets/xpm/biomes/city/tiles/tile_obstacle.xpm"
#include "../../assets/xpm/biomes/city/tiles/tile_boost.xpm"
#include "../../assets/xpm/biomes/city/tiles/tile_finish.xpm"
#include "../../assets/xpm/biomes/city/scenery/grass1.xpm"
#include "../../assets/xpm/biomes/city/scenery/tree.xpm"
#include "../../assets/xpm/biomes/city/objects/obstacle.xpm"
#include "../../assets/xpm/biomes/city/objects/boost.xpm"
#include "../../assets/xpm/biomes/city/objects/boost1.xpm"
#include "../../assets/xpm/biomes/city/objects/boost2.xpm"
#include "../../assets/xpm/biomes/city/objects/boost3.xpm"
#include "../../assets/xpm/biomes/city/objects/shield.xpm"
#include "../../assets/xpm/biomes/city/objects/shield_aura.xpm"
#include "../../assets/xpm/biomes/city/tiles/road.xpm"
#include "../../assets/xpm/biomes/city/tiles/inner_road_left.xpm"
#include "../../assets/xpm/biomes/city/tiles/inner_road_right.xpm"

/* ── desert ── */
#include "../../assets/xpm/biomes/desert/tiles/tile_road_desert.xpm"
#include "../../assets/xpm/biomes/desert/tiles/tile_sand.xpm"
#include "../../assets/xpm/biomes/desert/tiles/tile_divider.xpm"
#include "../../assets/xpm/biomes/desert/tiles/tile_finish_desert.xpm"
#include "../../assets/xpm/biomes/desert/scenery/cactus_tall.xpm"
#include "../../assets/xpm/biomes/desert/objects/obstacle_barrel.xpm"
#include "../../assets/xpm/biomes/desert/objects/obstacle_haybale.xpm"
#include "../../assets/xpm/biomes/desert/objects/oil_puddle.xpm"
#include "../../assets/xpm/biomes/desert/scenery/fence.xpm"
#include "../../assets/xpm/biomes/desert/tiles/tile_sand_pebbles.xpm"

/* ── forest / blossom ── */
#include "../../assets/xpm/biomes/forest/tiles/tile_road_forest.xpm"
#include "../../assets/xpm/biomes/forest/tiles/ground_forest.xpm"
#include "../../assets/xpm/biomes/forest/tiles/ground_forest2.xpm"
#include "../../assets/xpm/biomes/forest/tiles/tile_road_cobble.xpm"
#include "../../assets/xpm/biomes/forest/tiles/ground_forest_branches.xpm"
#include "../../assets/xpm/biomes/forest/tiles/blossom_wall.xpm"
#include "../../assets/xpm/biomes/forest/scenery/blossom_tree.xpm"
#include "../../assets/xpm/biomes/forest/objects/blossom_lantern.xpm"
#include "../../assets/xpm/biomes/forest/objects/blossom_branch.xpm"
#include "../../assets/xpm/biomes/forest/objects/blossom_stump.xpm"
#include "../../assets/xpm/biomes/forest/objects/blossom_log.xpm"

/* ── biome selector UI ── */
#include "../../assets/xpm/ui/screens/biome_select/biome_select_title.xpm"
#include "../../assets/xpm/ui/screens/biome_select/biome_label_city.xpm"
#include "../../assets/xpm/ui/screens/biome_select/biome_label_desert.xpm"
#include "../../assets/xpm/ui/screens/biome_select/biome_label_forest.xpm"

/* ── car sprites: 4 designs × 2 players × 4 damage states ── */
#include "../../assets/xpm/elements/cars/car1/p1/s1.xpm"
#include "../../assets/xpm/elements/cars/car1/p1/s2.xpm"
#include "../../assets/xpm/elements/cars/car1/p1/s3.xpm"
#include "../../assets/xpm/elements/cars/car1/p1/s4.xpm"
#include "../../assets/xpm/elements/cars/car1/p2/s1.xpm"
#include "../../assets/xpm/elements/cars/car1/p2/s2.xpm"
#include "../../assets/xpm/elements/cars/car1/p2/s3.xpm"
#include "../../assets/xpm/elements/cars/car1/p2/s4.xpm"

#include "../../assets/xpm/elements/cars/car2/p1/s1.xpm"
#include "../../assets/xpm/elements/cars/car2/p1/s2.xpm"
#include "../../assets/xpm/elements/cars/car2/p1/s3.xpm"
#include "../../assets/xpm/elements/cars/car2/p1/s4.xpm"
#include "../../assets/xpm/elements/cars/car2/p2/s1.xpm"
#include "../../assets/xpm/elements/cars/car2/p2/s2.xpm"
#include "../../assets/xpm/elements/cars/car2/p2/s3.xpm"
#include "../../assets/xpm/elements/cars/car2/p2/s4.xpm"

#include "../../assets/xpm/elements/cars/car3/p1/s1.xpm"
#include "../../assets/xpm/elements/cars/car3/p1/s2.xpm"
#include "../../assets/xpm/elements/cars/car3/p1/s3.xpm"
#include "../../assets/xpm/elements/cars/car3/p1/s4.xpm"
#include "../../assets/xpm/elements/cars/car3/p2/s1.xpm"
#include "../../assets/xpm/elements/cars/car3/p2/s2.xpm"
#include "../../assets/xpm/elements/cars/car3/p2/s3.xpm"
#include "../../assets/xpm/elements/cars/car3/p2/s4.xpm"

#include "../../assets/xpm/elements/cars/car4/p1/s1.xpm"
#include "../../assets/xpm/elements/cars/car4/p1/s2.xpm"
#include "../../assets/xpm/elements/cars/car4/p1/s3.xpm"
#include "../../assets/xpm/elements/cars/car4/p1/s4.xpm"
#include "../../assets/xpm/elements/cars/car4/p2/s1.xpm"
#include "../../assets/xpm/elements/cars/car4/p2/s2.xpm"
#include "../../assets/xpm/elements/cars/car4/p2/s3.xpm"
#include "../../assets/xpm/elements/cars/car4/p2/s4.xpm"

#include "../../assets/xpm/ui/screens/pause/pause_panel.xpm"
#include "../../assets/xpm/elements/nana_tiles_64x64/nana_0_0.xpm"
#include "../../assets/xpm/elements/nana_tiles_64x64/nana_0_1.xpm"
#include "../../assets/xpm/elements/nana_tiles_64x64/nana_0_2.xpm"
#include "../../assets/xpm/elements/nana_tiles_64x64/nana_0_3.xpm"
#include "../../assets/xpm/elements/nana_tiles_64x64/nana_1_0.xpm"
#include "../../assets/xpm/elements/nana_tiles_64x64/nana_1_1.xpm"
#include "../../assets/xpm/elements/nana_tiles_64x64/nana_1_2.xpm"
#include "../../assets/xpm/elements/nana_tiles_64x64/nana_1_3.xpm"
#include "../../assets/xpm/elements/nana_tiles_64x64/nana_2_0.xpm"
#include "../../assets/xpm/elements/nana_tiles_64x64/nana_2_1.xpm"
#include "../../assets/xpm/elements/nana_tiles_64x64/nana_2_2.xpm"
#include "../../assets/xpm/elements/nana_tiles_64x64/nana_2_3.xpm"
#include "../../assets/xpm/elements/nana_tiles_64x64/nana_3_0.xpm"
#include "../../assets/xpm/elements/nana_tiles_64x64/nana_3_1.xpm"
#include "../../assets/xpm/elements/nana_tiles_64x64/nana_3_2.xpm"
#include "../../assets/xpm/elements/nana_tiles_64x64/nana_3_3.xpm"
#include "../../assets/xpm/ui/screens/pause/pause_resume_btn.xpm"
#include "../../assets/xpm/ui/screens/pause/pause_resume_btn_sel.xpm"
#include "../../assets/xpm/ui/screens/pause/pause_quit_btn.xpm"
#include "../../assets/xpm/ui/screens/pause/pause_quit_btn_sel.xpm"

#include "../../assets/xpm/ui/hud/digits/digit_0.xpm"
#include "../../assets/xpm/ui/hud/digits/digit_1.xpm"
#include "../../assets/xpm/ui/hud/digits/digit_2.xpm"
#include "../../assets/xpm/ui/hud/digits/digit_3.xpm"
#include "../../assets/xpm/ui/hud/digits/digit_4.xpm"
#include "../../assets/xpm/ui/hud/digits/digit_5.xpm"
#include "../../assets/xpm/ui/hud/digits/digit_6.xpm"
#include "../../assets/xpm/ui/hud/digits/digit_7.xpm"
#include "../../assets/xpm/ui/hud/digits/digit_8.xpm"
#include "../../assets/xpm/ui/hud/digits/digit_9.xpm"
#include "../../assets/xpm/ui/hud/digits/digit_colon.xpm"

#include "../../assets/xpm/ui/screens/main/getaway_car_title.xpm"
#include "../../assets/xpm/ui/screens/main/start_button.xpm"
#include "../../assets/xpm/ui/screens/main/instructions_button.xpm"
#include "../../assets/xpm/ui/screens/main/leaderboard_button.xpm"
#include "../../assets/xpm/ui/screens/main/exit_button.xpm"
#include "../../assets/xpm/ui/hud/cursor.xpm"
#include "../../assets/xpm/ui/hud/heart.xpm"

#include "../../assets/xpm/ui/screens/modes/mode_select_title.xpm"
#include "../../assets/xpm/ui/screens/modes/mode_race_card.xpm"
#include "../../assets/xpm/ui/screens/modes/mode_endurance_card.xpm"
#include "../../assets/xpm/ui/screens/modes/title_race.xpm"
#include "../../assets/xpm/ui/screens/modes/title_endurance.xpm"

#include "../../assets/xpm/ui/screens/win/blue_wins.xpm"
#include "../../assets/xpm/ui/screens/win/red_wins.xpm"
#include "../../assets/xpm/ui/screens/win/win_play_again_btn.xpm"
#include "../../assets/xpm/ui/screens/win/win_menu_btn.xpm"

static const xpm_map_t car_fmt_xpms[4][CAR_PLAYER_COUNT][CAR_STATE_COUNT] = {
    { { (xpm_map_t)car1_p1_s1, (xpm_map_t)car1_p1_s2,
        (xpm_map_t)car1_p1_s3, (xpm_map_t)car1_p1_s4 },
      { (xpm_map_t)car1_p2_s1, (xpm_map_t)car1_p2_s2,
        (xpm_map_t)car1_p2_s3, (xpm_map_t)car1_p2_s4 } },
    { { (xpm_map_t)car2_p1_s1, (xpm_map_t)car2_p1_s2,
        (xpm_map_t)car2_p1_s3, (xpm_map_t)car2_p1_s4 },
      { (xpm_map_t)car2_p2_s1, (xpm_map_t)car2_p2_s2,
        (xpm_map_t)car2_p2_s3, (xpm_map_t)car2_p2_s4 } },
    { { (xpm_map_t)car3_p1_s1, (xpm_map_t)car3_p1_s2,
        (xpm_map_t)car3_p1_s3, (xpm_map_t)car3_p1_s4 },
      { (xpm_map_t)car3_p2_s1, (xpm_map_t)car3_p2_s2,
        (xpm_map_t)car3_p2_s3, (xpm_map_t)car3_p2_s4 } },
    { { (xpm_map_t)car4_p1_s1, (xpm_map_t)car4_p1_s2,
        (xpm_map_t)car4_p1_s3, (xpm_map_t)car4_p1_s4 },
      { (xpm_map_t)car4_p2_s1, (xpm_map_t)car4_p2_s2,
        (xpm_map_t)car4_p2_s3, (xpm_map_t)car4_p2_s4 } },
};

static Resources res;

int resources_load(void) {
    {
        int n = 4;
        for (int d = 0; d < n && d < CAR_FORMAT_MAX; d++)
            for (int p = 0; p < CAR_PLAYER_COUNT; p++)
                for (int s = 0; s < CAR_STATE_COUNT; s++) {
                    res.car_format_sprites[d][p][s] = create_sprite(car_fmt_xpms[d][p][s]);
                    if (!res.car_format_sprites[d][p][s]) return 1;
                }
        res.car_format_count = n;
        for (int p = 0; p < CAR_PLAYER_COUNT; p++)
            for (int s = 0; s < CAR_STATE_COUNT; s++)
                res.car_sprites[p][s] = res.car_format_sprites[0][p][s];
    }

    /* City tiles */
    res.tile_sprites[TRACK_THEME_CITY][TILE_EMPTY]    = create_sprite((xpm_map_t)tile_road_xpm);
    res.tile_sprites[TRACK_THEME_CITY][TILE_OBSTACLE] = create_sprite((xpm_map_t)tile_obstacle_xpm);
    res.tile_sprites[TRACK_THEME_CITY][TILE_BOOST]    = create_sprite((xpm_map_t)tile_boost_xpm);
    res.tile_sprites[TRACK_THEME_CITY][TILE_FINISH]   = create_sprite((xpm_map_t)tile_finish_xpm);
    for (int t = 0; t < 4; t++)
        if (!res.tile_sprites[TRACK_THEME_CITY][t]) return 1;

    /* Desert tiles */
    res.tile_sprites[TRACK_THEME_DESERT][TILE_EMPTY]    = create_sprite((xpm_map_t)tile_road_desert_xpm);
    res.tile_sprites[TRACK_THEME_DESERT][TILE_OBSTACLE] = create_sprite((xpm_map_t)tile_obstacle_xpm);
    res.tile_sprites[TRACK_THEME_DESERT][TILE_BOOST]    = create_sprite((xpm_map_t)tile_boost_xpm);
    res.tile_sprites[TRACK_THEME_DESERT][TILE_FINISH]   = create_sprite((xpm_map_t)tile_finish_desert_xpm);
    for (int t = 0; t < 4; t++)
        if (!res.tile_sprites[TRACK_THEME_DESERT][t]) return 1;

    /* Forest / Blossom tiles */
    res.tile_sprites[TRACK_THEME_FOREST][TILE_EMPTY]    = create_sprite((xpm_map_t)tile_road_forest_xpm);
    res.tile_sprites[TRACK_THEME_FOREST][TILE_OBSTACLE] = create_sprite((xpm_map_t)tile_obstacle_xpm);
    res.tile_sprites[TRACK_THEME_FOREST][TILE_BOOST]    = create_sprite((xpm_map_t)tile_boost_xpm);
    res.tile_sprites[TRACK_THEME_FOREST][TILE_FINISH]   = create_sprite((xpm_map_t)tile_finish_xpm);
    for (int t = 0; t < 4; t++)
        if (!res.tile_sprites[TRACK_THEME_FOREST][t]) return 1;

    res.ground_tiles[TRACK_THEME_CITY][GROUND_TILE_SOIL]   = create_sprite((xpm_map_t)grass1_xpm);
    res.ground_tiles[TRACK_THEME_DESERT][GROUND_TILE_SOIL] = create_sprite((xpm_map_t)tile_sand_xpm);
    res.ground_tiles[TRACK_THEME_FOREST][GROUND_TILE_SOIL] = create_sprite((xpm_map_t)ground_forest_xpm);
    for (int i = 0; i < TRACK_THEME_COUNT; i++)
        if (!res.ground_tiles[i][GROUND_TILE_SOIL]) return 1;

    res.ground_tiles[TRACK_THEME_FOREST][GROUND_TILE_ROCKS]  = create_sprite((xpm_map_t)ground_forest2_xpm);
    if (!res.ground_tiles[TRACK_THEME_FOREST][GROUND_TILE_ROCKS]) return 1;
    res.ground_tiles[TRACK_THEME_FOREST][GROUND_TILE_COBBLE] = create_sprite((xpm_map_t)tile_road_cobble_xpm);
    if (!res.ground_tiles[TRACK_THEME_FOREST][GROUND_TILE_COBBLE]) return 1;
    res.ground_tiles[TRACK_THEME_FOREST][GROUND_TILE_BLOCK]  = create_sprite((xpm_map_t)ground_forest_branches_xpm);
    if (!res.ground_tiles[TRACK_THEME_FOREST][GROUND_TILE_BLOCK]) return 1;

    res.wall_sprites[TRACK_THEME_FOREST] = create_sprite((xpm_map_t)blossom_wall_xpm);
    if (!res.wall_sprites[TRACK_THEME_FOREST]) return 1;

    res.scenery_sprites[TRACK_THEME_CITY]   = create_sprite((xpm_map_t)tree);
    res.scenery_sprites[TRACK_THEME_DESERT] = create_sprite((xpm_map_t)cactus_tall_xpm);
    res.scenery_sprites[TRACK_THEME_FOREST] = create_sprite((xpm_map_t)blossom_tree_xpm);
    for (int i = 0; i < TRACK_THEME_COUNT; i++)
        if (!res.scenery_sprites[i]) return 1;

    res.divider_sprite = create_sprite((xpm_map_t)tile_divider_xpm);
    if (!res.divider_sprite) return 1;

    res.obstacle_sprites[TRACK_THEME_CITY]   = create_sprite((xpm_map_t)obstacle_xpm);
    res.obstacle_sprites[TRACK_THEME_DESERT] = create_sprite((xpm_map_t)obstacle_barrel_xpm);
    res.obstacle_sprites[TRACK_THEME_FOREST] = create_sprite((xpm_map_t)blossom_lantern_xpm);
    for (int i = 0; i < 3; i++)
        if (!res.obstacle_sprites[i]) return 1;

    {
        static xpm_map_t forest_obs_xpms[4] = {
            (xpm_map_t)blossom_branch_xpm,
            (xpm_map_t)blossom_stump_xpm,
            (xpm_map_t)blossom_log_xpm,
            (xpm_map_t)blossom_lantern_xpm,
        };
        for (int i = 0; i < 4; i++) {
            res.forest_obstacle_sprites[i] = create_sprite(forest_obs_xpms[i]);
            if (!res.forest_obstacle_sprites[i]) return 1;
        }
    }

    res.haybale_sprite = create_sprite((xpm_map_t)obstacle_haybale_xpm);
    if (!res.haybale_sprite) return 1;

    res.oil_puddle_sprite   = create_sprite((xpm_map_t)oil_puddle_xpm);
    res.fence_sprite        = create_sprite((xpm_map_t)fence_xpm);
    res.sand_pebbles_sprite = create_sprite((xpm_map_t)tile_sand_pebbles_xpm);
    if (!res.oil_puddle_sprite || !res.fence_sprite || !res.sand_pebbles_sprite) return 1;

    {
        static xpm_map_t city_obs_xpms[16] = {
            (xpm_map_t)item_1_1_xpm, (xpm_map_t)item_1_2_xpm,
            (xpm_map_t)item_1_3_xpm, (xpm_map_t)item_1_4_xpm,
            (xpm_map_t)item_2_1_xpm, (xpm_map_t)item_2_2_xpm,
            (xpm_map_t)item_2_3_xpm, (xpm_map_t)item_2_4_xpm,
            (xpm_map_t)item_3_1_xpm, (xpm_map_t)item_3_2_xpm,
            (xpm_map_t)item_3_3_xpm, (xpm_map_t)item_3_4_xpm,
            (xpm_map_t)item_4_1_xpm, (xpm_map_t)item_4_2_xpm,
            (xpm_map_t)item_4_3_xpm, (xpm_map_t)item_4_4_xpm,
        };
        for (int i = 0; i < 16; i++) {
            res.city_obstacle_sprites[i] = create_sprite(city_obs_xpms[i]);
            if (!res.city_obstacle_sprites[i]) return 1;
        }
    }

    res.menu_title     = create_sprite((xpm_map_t)getaway_car_title);
    if (!res.menu_title) return 1;

    res.menu_start_btn = create_sprite((xpm_map_t)start_button);
    if (!res.menu_start_btn) return 1;

    res.menu_instructions_btn = create_sprite((xpm_map_t)instructions_button_xpm);

    res.menu_leaderboard_btn = create_sprite((xpm_map_t)leaderboard_button);
    if (!res.menu_leaderboard_btn) return 1;

    res.menu_exit_btn  = create_sprite((xpm_map_t)exit_button);
    if (!res.menu_exit_btn) return 1;

    res.boost_sprite = create_sprite((xpm_map_t)boost_xpm);
    if (!res.boost_sprite) return 1;

    {
        static xpm_map_t city_boost_xpms[3] = {
            (xpm_map_t)boost1, (xpm_map_t)boost2, (xpm_map_t)boost3,
        };
        for (int i = 0; i < 3; i++) {
            res.city_boost_sprites[i] = create_sprite(city_boost_xpms[i]);
            if (!res.city_boost_sprites[i]) return 1;
        }
    }

    res.pause_panel        = create_sprite((xpm_map_t)pause_panel_xpm);
    res.pause_resume_btn[0] = create_sprite((xpm_map_t)pause_resume_btn_xpm);
    res.pause_resume_btn[1] = create_sprite((xpm_map_t)pause_resume_btn_sel_xpm);
    res.pause_quit_btn[0]   = create_sprite((xpm_map_t)pause_quit_btn_xpm);
    res.pause_quit_btn[1]   = create_sprite((xpm_map_t)pause_quit_btn_sel_xpm);
    if (!res.pause_panel || !res.pause_resume_btn[0] || !res.pause_resume_btn[1]
     || !res.pause_quit_btn[0] || !res.pause_quit_btn[1]) return 1;

    res.cursor_sprite = create_sprite((xpm_map_t)cursor_xpm);
    if (!res.cursor_sprite) return 1;

    {
        static const xpm_map_t nana_xpms[16] = {
            (xpm_map_t)nana_0_0_xpm, (xpm_map_t)nana_0_1_xpm,
            (xpm_map_t)nana_0_2_xpm, (xpm_map_t)nana_0_3_xpm,
            (xpm_map_t)nana_1_0_xpm, (xpm_map_t)nana_1_1_xpm,
            (xpm_map_t)nana_1_2_xpm, (xpm_map_t)nana_1_3_xpm,
            (xpm_map_t)nana_2_0_xpm, (xpm_map_t)nana_2_1_xpm,
            (xpm_map_t)nana_2_2_xpm, (xpm_map_t)nana_2_3_xpm,
            (xpm_map_t)nana_3_0_xpm, (xpm_map_t)nana_3_1_xpm,
            (xpm_map_t)nana_3_2_xpm, (xpm_map_t)nana_3_3_xpm,
        };
        for (int i = 0; i < 16; i++) {
            res.banana_frames[i] = create_sprite(nana_xpms[i]);
            if (!res.banana_frames[i]) return 1;
        }
    }

    res.heart_sprite = create_sprite((xpm_map_t)heart_xpm);
    if (!res.heart_sprite) return 1;

    static xpm_map_t digit_xpms[10] = {
        (xpm_map_t)digit_0, (xpm_map_t)digit_1, (xpm_map_t)digit_2,
        (xpm_map_t)digit_3, (xpm_map_t)digit_4, (xpm_map_t)digit_5,
        (xpm_map_t)digit_6, (xpm_map_t)digit_7, (xpm_map_t)digit_8,
        (xpm_map_t)digit_9
    };
    for (int i = 0; i < 10; i++) {
        res.digit_sprites[i] = create_sprite(digit_xpms[i]);
        if (!res.digit_sprites[i]) return 1;
    }
    res.colon_sprite = create_sprite((xpm_map_t)digit_colon);
    if (!res.colon_sprite) return 1;

    res.mode_select_title   = create_sprite((xpm_map_t)mode_select_title);
    if (!res.mode_select_title) return 1;
    res.mode_race_card      = create_sprite((xpm_map_t)mode_race_card);
    if (!res.mode_race_card) return 1;
    res.mode_endurance_card = create_sprite((xpm_map_t)mode_endurance_card);
    if (!res.mode_endurance_card) return 1;
    res.mode_race_label      = create_sprite((xpm_map_t)title_race);
    if (!res.mode_race_label) return 1;
    res.mode_endurance_label = create_sprite((xpm_map_t)title_endurance);
    if (!res.mode_endurance_label) return 1;

    /* Biome selector UI */
    res.biome_select_title = create_sprite((xpm_map_t)biome_select_title);
    if (!res.biome_select_title) return 1;
    res.biome_labels[TRACK_THEME_CITY]   = create_sprite((xpm_map_t)biome_label_city);
    if (!res.biome_labels[TRACK_THEME_CITY])   return 1;
    res.biome_labels[TRACK_THEME_DESERT] = create_sprite((xpm_map_t)biome_label_desert);
    if (!res.biome_labels[TRACK_THEME_DESERT]) return 1;
    res.biome_labels[TRACK_THEME_FOREST] = create_sprite((xpm_map_t)biome_label_forest);
    if (!res.biome_labels[TRACK_THEME_FOREST]) return 1;

    res.win_img[0] = create_sprite((xpm_map_t)blue_wins);
    if (!res.win_img[0]) return 1;
    res.win_img[1] = create_sprite((xpm_map_t)red_wins);
    if (!res.win_img[1]) return 1;
    res.win_play_again_btn = create_sprite((xpm_map_t)win_play_again_btn);
    if (!res.win_play_again_btn) return 1;
    res.win_menu_btn = create_sprite((xpm_map_t)win_menu_btn);
    if (!res.win_menu_btn) return 1;

    res.shield_sprite = create_sprite((xpm_map_t)shield_xpm);
    if (!res.shield_sprite) return 1;
    res.shield_aura_sprite = create_sprite((xpm_map_t)shield_aura_xpm);
    if (!res.shield_aura_sprite) return 1;

    res.road_detail_sprite = create_sprite((xpm_map_t)road_xpm);
    if (!res.road_detail_sprite) return 1;
    res.inner_road_left_sprite  = create_sprite((xpm_map_t)inner_road_left_xpm);
    if (!res.inner_road_left_sprite) return 1;
    res.inner_road_right_sprite = create_sprite((xpm_map_t)inner_road_right_xpm);
    if (!res.inner_road_right_sprite) return 1;

    return 0;
}

void resources_destroy(void) {
    for (int p = 0; p < CAR_PLAYER_COUNT; p++)
        for (int s = 0; s < CAR_STATE_COUNT; s++)
            res.car_sprites[p][s] = NULL;
    for (int f = 0; f < res.car_format_count; f++)
        for (int p = 0; p < CAR_PLAYER_COUNT; p++)
            for (int s = 0; s < CAR_STATE_COUNT; s++)
                if (res.car_format_sprites[f][p][s]) {
                    sprite_destroy(res.car_format_sprites[f][p][s]);
                    res.car_format_sprites[f][p][s] = NULL;
                }
    res.car_format_count = 0;
    for (int th = 0; th < TRACK_THEME_COUNT; th++)
        for (int t = 0; t < 4; t++)
            if (res.tile_sprites[th][t]) { sprite_destroy(res.tile_sprites[th][t]); res.tile_sprites[th][t] = NULL; }
    for (int i = 0; i < TRACK_THEME_COUNT; i++) {
        for (int v = 0; v < GROUND_TILE_COUNT; v++)
            if (res.ground_tiles[i][v]) { sprite_destroy(res.ground_tiles[i][v]); res.ground_tiles[i][v] = NULL; }
        if (res.wall_sprites[i])     { sprite_destroy(res.wall_sprites[i]);     res.wall_sprites[i]     = NULL; }
        if (res.scenery_sprites[i])  { sprite_destroy(res.scenery_sprites[i]);  res.scenery_sprites[i]  = NULL; }
        if (res.obstacle_sprites[i]) { sprite_destroy(res.obstacle_sprites[i]); res.obstacle_sprites[i] = NULL; }
        if (res.biome_labels[i])     { sprite_destroy(res.biome_labels[i]);     res.biome_labels[i]     = NULL; }
    }
    if (res.biome_select_title) { sprite_destroy(res.biome_select_title); res.biome_select_title = NULL; }
    if (res.divider_sprite)     { sprite_destroy(res.divider_sprite);     res.divider_sprite     = NULL; }
    if (res.haybale_sprite)     { sprite_destroy(res.haybale_sprite);     res.haybale_sprite     = NULL; }
    for (int i = 0; i < 16; i++)
        if (res.city_obstacle_sprites[i]) { sprite_destroy(res.city_obstacle_sprites[i]); res.city_obstacle_sprites[i] = NULL; }
    for (int i = 0; i < 4; i++)
        if (res.forest_obstacle_sprites[i]) { sprite_destroy(res.forest_obstacle_sprites[i]); res.forest_obstacle_sprites[i] = NULL; }
    if (res.boost_sprite)    { sprite_destroy(res.boost_sprite);    res.boost_sprite    = NULL; }
    for (int i = 0; i < 3; i++)
        if (res.city_boost_sprites[i]) { sprite_destroy(res.city_boost_sprites[i]); res.city_boost_sprites[i] = NULL; }
    if (res.pause_panel)     { sprite_destroy(res.pause_panel);     res.pause_panel     = NULL; }
    for (int i = 0; i < 16; i++)
        if (res.banana_frames[i]) { sprite_destroy(res.banana_frames[i]); res.banana_frames[i] = NULL; }
    if (res.oil_puddle_sprite)  { sprite_destroy(res.oil_puddle_sprite);  res.oil_puddle_sprite  = NULL; }
    if (res.fence_sprite)       { sprite_destroy(res.fence_sprite);       res.fence_sprite       = NULL; }
    if (res.sand_pebbles_sprite){ sprite_destroy(res.sand_pebbles_sprite);res.sand_pebbles_sprite= NULL; }
    for (int i = 0; i < 2; i++) {
        if (res.pause_resume_btn[i]) { sprite_destroy(res.pause_resume_btn[i]); res.pause_resume_btn[i] = NULL; }
        if (res.pause_quit_btn[i])   { sprite_destroy(res.pause_quit_btn[i]);   res.pause_quit_btn[i]   = NULL; }
    }
    if (res.menu_title)            { sprite_destroy(res.menu_title);            res.menu_title            = NULL; }
    if (res.menu_start_btn)        { sprite_destroy(res.menu_start_btn);        res.menu_start_btn        = NULL; }
    if (res.menu_instructions_btn) { sprite_destroy(res.menu_instructions_btn); res.menu_instructions_btn = NULL; }
    if (res.menu_leaderboard_btn)  { sprite_destroy(res.menu_leaderboard_btn);  res.menu_leaderboard_btn  = NULL; }
    if (res.menu_exit_btn)         { sprite_destroy(res.menu_exit_btn);         res.menu_exit_btn         = NULL; }
    if (res.cursor_sprite)   { sprite_destroy(res.cursor_sprite);   res.cursor_sprite   = NULL; }
    if (res.heart_sprite)    { sprite_destroy(res.heart_sprite);    res.heart_sprite    = NULL; }
    for (int i = 0; i < 10; i++)
        if (res.digit_sprites[i]) { sprite_destroy(res.digit_sprites[i]); res.digit_sprites[i] = NULL; }
    if (res.colon_sprite) { sprite_destroy(res.colon_sprite); res.colon_sprite = NULL; }
    if (res.mode_select_title)   { sprite_destroy(res.mode_select_title);   res.mode_select_title   = NULL; }
    if (res.mode_race_card)      { sprite_destroy(res.mode_race_card);      res.mode_race_card      = NULL; }
    if (res.mode_endurance_card) { sprite_destroy(res.mode_endurance_card); res.mode_endurance_card = NULL; }
    if (res.mode_race_label)      { sprite_destroy(res.mode_race_label);      res.mode_race_label      = NULL; }
    if (res.mode_endurance_label) { sprite_destroy(res.mode_endurance_label); res.mode_endurance_label = NULL; }
    for (int i = 0; i < 2; i++)
        if (res.win_img[i]) { sprite_destroy(res.win_img[i]); res.win_img[i] = NULL; }
    if (res.win_play_again_btn) { sprite_destroy(res.win_play_again_btn); res.win_play_again_btn = NULL; }
    if (res.win_menu_btn)       { sprite_destroy(res.win_menu_btn);       res.win_menu_btn       = NULL; }
    if (res.shield_sprite)      { sprite_destroy(res.shield_sprite);      res.shield_sprite      = NULL; }
    if (res.shield_aura_sprite) { sprite_destroy(res.shield_aura_sprite); res.shield_aura_sprite = NULL; }
    if (res.road_detail_sprite)       { sprite_destroy(res.road_detail_sprite);       res.road_detail_sprite       = NULL; }
    if (res.inner_road_left_sprite)   { sprite_destroy(res.inner_road_left_sprite);   res.inner_road_left_sprite   = NULL; }
    if (res.inner_road_right_sprite)  { sprite_destroy(res.inner_road_right_sprite);  res.inner_road_right_sprite  = NULL; }
}

Sprite* resources_get_car_sprite(int player, int state) {
    Sprite *sp = res.car_sprites[player][state];
    if (!sp) sp = res.car_sprites[player][CAR_STATE_NORMAL];
    return sp;
}

Sprite* resources_get_obstacle_sprite(void) {
    return res.obstacle_sprites[TRACK_THEME_CITY];
}

Sprite* resources_get_boost_sprite(void) {
    return res.boost_sprite;
}

Sprite* resources_get_tile_sprite(int type) {
    return res.tile_sprites[TRACK_THEME_CITY][type];
}

Sprite* resources_get_tile_sprite_themed(int type, int theme) {
    if (theme < 0 || theme >= TRACK_THEME_COUNT) return res.tile_sprites[TRACK_THEME_CITY][type];
    return res.tile_sprites[theme][type];
}

Sprite* resources_get_ground_tile(int theme, int variant) {
    if (theme < 0 || theme >= TRACK_THEME_COUNT) return res.ground_tiles[TRACK_THEME_CITY][GROUND_TILE_SOIL];
    if (variant < 0 || variant >= GROUND_TILE_COUNT) return res.ground_tiles[theme][GROUND_TILE_SOIL];
    return res.ground_tiles[theme][variant];
}

Sprite* resources_get_ground_sprite(int theme) {
    if (theme < 0 || theme >= TRACK_THEME_COUNT) return res.ground_tiles[TRACK_THEME_CITY][GROUND_TILE_SOIL];
    return res.ground_tiles[theme][GROUND_TILE_SOIL];
}

Sprite* resources_get_wall_sprite(int theme) {
    if (theme < 0 || theme >= TRACK_THEME_COUNT) return NULL;
    return res.wall_sprites[theme];
}

Sprite* resources_get_scenery_sprite(int theme) {
    if (theme < 0 || theme >= TRACK_THEME_COUNT) return res.scenery_sprites[TRACK_THEME_CITY];
    return res.scenery_sprites[theme];
}

Sprite* resources_get_divider_sprite(void) { return res.divider_sprite; }


Sprite* resources_get_pause_panel(void) {
    return res.pause_panel;
}

Sprite* resources_get_pause_resume_btn(int selected) {
    return res.pause_resume_btn[selected ? 1 : 0];
}

Sprite* resources_get_pause_quit_btn(int selected) {
    return res.pause_quit_btn[selected ? 1 : 0];
}

Sprite* resources_get_menu_title(void)           { return res.menu_title; }
Sprite* resources_get_menu_start_btn(void)        { return res.menu_start_btn; }
Sprite* resources_get_menu_instructions_btn(void) { return res.menu_instructions_btn; }
Sprite* resources_get_menu_leaderboard_btn(void)  { return res.menu_leaderboard_btn; }
Sprite* resources_get_menu_exit_btn(void)         { return res.menu_exit_btn; }
Sprite* resources_get_cursor_sprite(void)  { return res.cursor_sprite; }
Sprite* resources_get_banana_sprite(uint32_t tick) {
    return res.banana_frames[(tick / 4) % 16];
}
Sprite* resources_get_heart_sprite(void)   { return res.heart_sprite; }

Sprite* resources_get_digit_sprite(int digit) {
    if (digit < 0 || digit > 9) return NULL;
    return res.digit_sprites[digit];
}

Sprite* resources_get_colon_sprite(void) { return res.colon_sprite; }

Sprite* resources_get_obstacle_sprite_themed(int theme) {
    if (theme < 0 || theme >= TRACK_THEME_COUNT) return res.obstacle_sprites[TRACK_THEME_CITY];
    return res.obstacle_sprites[theme];
}

Sprite* resources_get_fence_sprite(void)        { return res.fence_sprite; }
Sprite* resources_get_oil_puddle_sprite(void)   { return res.oil_puddle_sprite; }
Sprite* resources_get_sand_pebbles_sprite(void) { return res.sand_pebbles_sprite; }
Sprite* resources_get_mode_select_title(void)   { return res.mode_select_title; }
Sprite* resources_get_mode_race_card(void)       { return res.mode_race_card; }
Sprite* resources_get_mode_endurance_card(void)  { return res.mode_endurance_card; }
Sprite* resources_get_mode_race_label(void)      { return res.mode_race_label; }
Sprite* resources_get_mode_endurance_label(void) { return res.mode_endurance_label; }

int resources_get_car_format_count(void) { return res.car_format_count; }

Sprite* resources_get_car_format_preview(int fmt, int player) {
    if (fmt < 0 || fmt >= res.car_format_count || player < 0 || player > 1) return NULL;
    return res.car_format_sprites[fmt][player][CAR_STATE_NORMAL];
}

void resources_apply_car_format(int fmt1, int fmt2) {
    if (fmt1 < 0 || fmt1 >= res.car_format_count) return;
    if (fmt2 < 0 || fmt2 >= res.car_format_count) return;
    for (int s = 0; s < CAR_STATE_COUNT; s++) {
        if (res.car_format_sprites[fmt1][0][s])
            res.car_sprites[0][s] = res.car_format_sprites[fmt1][0][s];
        if (res.car_format_sprites[fmt2][1][s])
            res.car_sprites[1][s] = res.car_format_sprites[fmt2][1][s];
    }
}

Sprite* resources_get_biome_select_title(void) { return res.biome_select_title; }

Sprite* resources_get_biome_label(int theme) {
    if (theme < 0 || theme >= TRACK_THEME_COUNT) return NULL;
    return res.biome_labels[theme];
}

Sprite* resources_get_win_img(int winner) {
    if (winner == 1) return res.win_img[0]; /* blue wins */
    if (winner == 2) return res.win_img[1]; /* red wins  */
    return NULL;
}
Sprite* resources_get_win_play_again_btn(void) { return res.win_play_again_btn; }
Sprite* resources_get_win_menu_btn(void)       { return res.win_menu_btn; }

Sprite* resources_get_city_obstacle_sprite(int idx) {
    if (idx < 0 || idx >= 16) return res.city_obstacle_sprites[0];
    return res.city_obstacle_sprites[idx];
}

Sprite* resources_get_city_boost_sprite(int idx) {
    if (idx < 0 || idx >= 3) return res.city_boost_sprites[0];
    return res.city_boost_sprites[idx];
}

Sprite* resources_get_shield_sprite(void)      { return res.shield_sprite; }
Sprite* resources_get_shield_aura_sprite(void) { return res.shield_aura_sprite; }
Sprite* resources_get_road_detail_sprite(void)      { return res.road_detail_sprite; }
Sprite* resources_get_inner_road_left_sprite(void)  { return res.inner_road_left_sprite; }
Sprite* resources_get_inner_road_right_sprite(void) { return res.inner_road_right_sprite; }

Sprite* resources_get_forest_obstacle_sprite(int idx) {
    return res.forest_obstacle_sprites[((unsigned int)idx) % 4];
}
