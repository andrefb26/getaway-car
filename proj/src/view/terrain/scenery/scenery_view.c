#include "scenery_view.h"
#include "../../view.h"
#include "../../../model/resources/resources.h"
#include "../../../controller/palette/palette.h"
#include <math.h>

#define STRIP_TILES  3
#include "config.h"
#define WALL_COL_L   2
#define WALL_COL_R   0

static uint8_t biome_bg_color(TrackTheme theme) {
    switch (theme) {
        case TRACK_THEME_DESERT: return PAL_GRASS_DRY;
        case TRACK_THEME_FOREST: return PAL_TREE_TRUNK;
        default:                 return PAL_GRASS_BASE;
    }
}


void scenery_view_draw(const Scenery *s, const Track *track, TrackTheme theme) {
    if (!s || !track) return;

    int tile     = TRACK_TILE_HEIGHT;
    int off      = s->scroll_offset;
    int road_end = ROAD_OFFSET_X + 10 * CAR_LANE_WIDTH;
    int strip_w  = STRIP_TILES * tile;

    draw_rect(0,        0, strip_w, SCREEN_H, biome_bg_color(theme));
    draw_rect(road_end, 0, strip_w, SCREEN_H, biome_bg_color(theme));

    Sprite *tree  = resources_get_scenery_sprite(theme);
    Sprite *fence = (theme == TRACK_THEME_DESERT) ? resources_get_fence_sprite() : NULL;
    Sprite *wall  = resources_get_wall_sprite(theme);

    Sprite *variants[GROUND_TILE_COUNT];
    for (int v = 0; v < GROUND_TILE_COUNT; v++)
        variants[v] = resources_get_ground_tile(theme, v);

    /* Scrolling ground tiles */
    for (int screen_row = 0; screen_row <= TRACK_VISIBLE_ROWS; screen_row++) {
        int y  = (screen_row - 1) * tile + off;
        int lr = track->scroll_row + screen_row - 1;
        if (lr < 0) lr = 0;

        for (int col = 0; col < STRIP_TILES; col++) {
            /* LEFT strip */
            if (theme != TRACK_THEME_FOREST) {
                Sprite *g = variants[GROUND_TILE_SOIL];
                if (g) draw_sprite(g, col * tile, y);
            }

            /* RIGHT strip — col 0 is road-adjacent */
            int rcol = STRIP_TILES - 1 - col;
            if (theme != TRACK_THEME_FOREST) {
                Sprite *g = variants[GROUND_TILE_SOIL];
                if (g) draw_sprite(g, road_end + rcol * tile, y);
            }
        }

        if (wall) {
            draw_sprite(wall, WALL_COL_L * tile, y);
            draw_sprite(wall, road_end + WALL_COL_R * tile, y);
        }
        if (fence) {
            draw_sprite(fence, ROAD_OFFSET_X - tile, y);
            draw_sprite(fence, road_end, y);
        }
    }

    int screen_h = TRACK_VISIBLE_ROWS * tile;
    for (int i = 0; i < s->count; i++) {
        int sx = s->trees[i].screen_x;
        int sy = (int)round(s->trees[i].screen_y);
        if (sy + TREE_SIZE < 0 || sy >= screen_h) continue;

        Sprite *obj;
        if (theme == TRACK_THEME_FOREST) {
            int slot = i % 3;
            if (slot == 1 && wall)
                obj = wall;
            else if (slot == 2)
                obj = resources_get_forest_obstacle_sprite(i);
            else
                obj = tree;
        } else {
            obj = tree;
        }
        if (obj) draw_sprite(obj, sx, sy);
    }
}
