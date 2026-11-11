#include "track_view.h"
#include "../../../model/resources/resources.h"
#include "../../view.h"
#include "../../../model/elements/car/car.h"

void track_view_draw(const Track *track) {
    if (!track) return;

    for (int screen_row = 0; screen_row <= TRACK_VISIBLE_ROWS; screen_row++) {
        int y = screen_row * TRACK_TILE_HEIGHT + (int)track->scroll_offset;
        for (int lane = 0; lane < TRACK_LANES; lane++) {
            int lr   = track->scroll_row + 2 * CAR_SCREEN_ROW - screen_row;
            TileType type = track_get_tile(track, lr, lane);
            Sprite *sp = resources_get_tile_sprite_themed(type, track->theme);

            /* Mix alternate road tile: cycle 1-main / 2-alt / 2-main per lane */
            if (type == TILE_EMPTY) {
                Sprite *alt = resources_get_ground_tile(track->theme, GROUND_TILE_COBBLE);
                if (alt) {
                    int pos = (lr + lane * 2) % 5;
                    if (pos >= 1 && pos <= 2) sp = alt;
                }
            }

            if (!sp) continue;
            int x = ROAD_OFFSET_X + lane * CAR_LANE_WIDTH;
            draw_sprite(sp, x, y);
            if (track->theme == TRACK_THEME_CITY && type == TILE_EMPTY) {
                if (lane == PLAYER1_LANE_END) {
                    Sprite *inner = resources_get_inner_road_left_sprite();
                    if (inner) draw_sprite(inner, x, y);
                } else if (lane == PLAYER2_LANE_START) {
                    Sprite *inner = resources_get_inner_road_right_sprite();
                    if (inner) draw_sprite(inner, x, y);
                } else {
                    Sprite *detail = resources_get_road_detail_sprite();
                    if (detail) draw_sprite(detail, x, y);
                }
            }
        }
    }
}
