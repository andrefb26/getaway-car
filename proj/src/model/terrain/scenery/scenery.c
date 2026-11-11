#include "scenery.h"
#include "../../elements/car/car.h"
#include <stdlib.h>

#define GRASS_MARGIN 20

#define LEFT_X_MIN  (GRASS_MARGIN)
#define LEFT_X_MAX  (192 - GRASS_MARGIN - TREE_SIZE)
#define RIGHT_BASE  (192 + 10 * CAR_LANE_WIDTH)
#define RIGHT_X_MIN (RIGHT_BASE + GRASS_MARGIN)
#define RIGHT_X_MAX (RIGHT_BASE + 192 - GRASS_MARGIN - TREE_SIZE)

/* Forest: wall col 2 left (x=128–191), wall col 0 right (x=832–895) — no trees there */
#define LEFT_X_MAX_FOREST  (128 - GRASS_MARGIN - TREE_SIZE)
#define RIGHT_X_MIN_FOREST (RIGHT_BASE + 64 + GRASS_MARGIN)
#define RIGHT_X_MAX_FOREST RIGHT_X_MAX


Scenery* scenery_create(TrackTheme theme) {
    Scenery *s = malloc(sizeof(Scenery));
    if (!s) return NULL;

    s->scroll_offset = 0.0f;
    s->count = 0;

    int lx_min = LEFT_X_MIN;
    int lx_max = (theme == TRACK_THEME_FOREST) ? LEFT_X_MAX_FOREST  : LEFT_X_MAX;
    int rx_min = (theme == TRACK_THEME_FOREST) ? RIGHT_X_MIN_FOREST : RIGHT_X_MIN;
    int rx_max = (theme == TRACK_THEME_FOREST) ? RIGHT_X_MAX_FOREST : RIGHT_X_MAX;

    int left_range  = lx_max - lx_min + 1;
    int right_range = rx_max - rx_min + 1;

    if (theme == TRACK_THEME_FOREST) {
        /* One object per side every 5 rows → ~2–3 visible per side at any time */
        for (int row = 0; row < TRACK_TOTAL_ROWS && s->count < MAX_TREES - 2; row += 5) {
            int actual_row = row + (rand() % 4);
            if (left_range > 0) {
                s->trees[s->count].logical_row = actual_row;
                s->trees[s->count].screen_x    = lx_min + rand() % left_range;
                s->trees[s->count].screen_y    = 0;
                s->count++;
            }
            if (right_range > 0 && s->count < MAX_TREES) {
                s->trees[s->count].logical_row = actual_row;
                s->trees[s->count].screen_x    = rx_min + rand() % right_range;
                s->trees[s->count].screen_y    = 0;
                s->count++;
            }
        }
    } else {
        for (int row = 0; row < TRACK_TOTAL_ROWS && s->count < MAX_TREES - 2; row += 4) {
            int actual_row = row + rand() % 3;
            if (rand() % 10 < 7 && left_range > 0) {
                s->trees[s->count].logical_row = actual_row;
                s->trees[s->count].screen_x    = lx_min + rand() % left_range;
                s->trees[s->count].screen_y    = 0;
                s->count++;
            }
            if (rand() % 10 < 7 && right_range > 0 && s->count < MAX_TREES) {
                s->trees[s->count].logical_row = actual_row;
                s->trees[s->count].screen_x    = rx_min + rand() % right_range;
                s->trees[s->count].screen_y    = 0;
                s->count++;
            }
        }
    }

    return s;
}

void scenery_update(Scenery *s, const Track *track) {
    if (!s || !track) return;

    s->scroll_offset = track->scroll_offset;

    for (int i = 0; i < s->count; i++) {
        int screen_row = s->trees[i].logical_row - track->scroll_row;
        s->trees[i].screen_y = (double)((2 * CAR_SCREEN_ROW - screen_row) * TRACK_TILE_HEIGHT)
                             + (double)track->scroll_offset;
    }
}

void scenery_destroy(Scenery *s) {
    free(s);
}
