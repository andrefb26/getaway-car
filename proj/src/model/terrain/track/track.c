#include "track.h"
#include <stdlib.h>
#include <string.h>

// Probabilidades de geração aleatória (em percentagem aproximada)
#define PROB_BOOST          0     // boosts geridos como objetos em game.c
#define SCROLL_SPEED_INITIAL 2.0f
#define SCROLL_SPEED_MAX    12.0f
#define SCROLL_ACCELERATION  0.002f

// ---------------------------------------------------------------------------
// Geração aleatória da grelha
// ---------------------------------------------------------------------------

static TileType generate_tile(int row, int lane) {
    if (row == TRACK_TOTAL_ROWS - 1) return TILE_FINISH;
    if (row < 5)                     return TILE_EMPTY;

    int r = rand() % 100;
    if (r < PROB_BOOST) return TILE_BOOST;

    return TILE_EMPTY;
}

static void generate_grid(Track* track) {
    for (int row = 0; row < TRACK_TOTAL_ROWS; row++) {

        // Gerar cada metade da pista independentemente
        // para garantir que cada jogador tem sempre pelo menos uma faixa livre
        for (int player = 0; player < 2; player++) {

            int lane_start = (player == 0) ? PLAYER1_LANE_START : PLAYER2_LANE_START;

            int obstacle_count = 0;
            TileType proposed[TRACK_LANES_PER_PLAYER];

            for (int i = 0; i < TRACK_LANES_PER_PLAYER; i++) {
                proposed[i] = generate_tile(row, lane_start + i);
                if (proposed[i] == TILE_OBSTACLE) obstacle_count++;
            }

            // Se todas as faixas do jogador têm obstáculo, liberta uma aleatória
            if (obstacle_count == TRACK_LANES_PER_PLAYER) {
                proposed[rand() % TRACK_LANES_PER_PLAYER] = TILE_EMPTY;
            }

            for (int i = 0; i < TRACK_LANES_PER_PLAYER; i++) {
                track->grid[row][lane_start + i] = proposed[i];
            }
        }
    }
}

// ---------------------------------------------------------------------------
// Construtor / Destrutor
// ---------------------------------------------------------------------------

Track* create_track(TrackTheme theme) {
    Track* track = (Track*) malloc(sizeof(Track));
    if (track == NULL) return NULL;

    memset(track->grid, TILE_EMPTY, sizeof(track->grid));

    track->scroll_row    = 0;
    track->scroll_offset = 0;
    track->scroll_accum  = 0.0f;
    track->scroll_speed  = SCROLL_SPEED_INITIAL;
    track->theme         = theme;
    track->infinite      = false;

    generate_grid(track);

    return track;
}

void destroy_track(Track* track) {
    if (track != NULL) {
        free(track);
    }
}

// ---------------------------------------------------------------------------
// Scroll
// ---------------------------------------------------------------------------

void track_update(Track* track) {
    if (track == NULL) return;
    if (!track->infinite && track_is_finished(track)) return;

    if (track->scroll_speed < SCROLL_SPEED_MAX)
        track->scroll_speed += SCROLL_ACCELERATION;

    track->scroll_accum += track->scroll_speed;
    int pixels = (int)track->scroll_accum;
    track->scroll_accum -= (float)pixels;
    track->scroll_offset += pixels;

    while (track->scroll_offset >= TRACK_TILE_HEIGHT) {
        track->scroll_offset -= TRACK_TILE_HEIGHT;
        track->scroll_row++;
    }
}

// ---------------------------------------------------------------------------
// Acesso à grelha
// ---------------------------------------------------------------------------

TileType track_get_tile(const Track* track, int row, int lane) {
    if (track == NULL)          return TILE_EMPTY;
    if (row  < 0 || row  >= TRACK_TOTAL_ROWS) return TILE_EMPTY;
    if (lane < 0 || lane >= TRACK_LANES)      return TILE_EMPTY;

    return track->grid[row][lane];
}

TileType track_get_visible_tile(const Track* track, int screen_row, int lane) {
    if (track == NULL) return TILE_EMPTY;

    int logical_row = track->scroll_row + screen_row;
    return track_get_tile(track, logical_row, lane);
}

TileType track_check_car_tile(const Track* track, int lane) {
    if (track == NULL) return TILE_EMPTY;

    // O carro está sempre na linha de ecrã CAR_SCREEN_ROW
    int logical_row = track->scroll_row + CAR_SCREEN_ROW;
    return track_get_tile(track, logical_row, lane);
}

void track_clear_tile(Track* track, int row, int lane) {
    if (track == NULL)          return;
    if (row  < 0 || row  >= TRACK_TOTAL_ROWS) return;
    if (lane < 0 || lane >= TRACK_LANES)      return;

    track->grid[row][lane] = TILE_EMPTY;
}

bool track_is_finished(const Track* track) {
    if (track == NULL) return false;

    // A corrida termina quando o scroll chega à linha da meta
    return track->scroll_row + CAR_SCREEN_ROW >= TRACK_TOTAL_ROWS - 1;
}
