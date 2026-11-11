/**
 * @file car.h
 * @brief Player car model: state, movement, damage and boost logic.
 */

#ifndef CAR_H
#define CAR_H

#include "../../common/element/element.h"
#include "../../terrain/track/track.h"
#include <stdbool.h>

/** @defgroup car_dimensions Car size constants
 * @{ */
#define CAR_LANE_WIDTH  64                    /**< Width of one lane in pixels. */
#define CAR_WIDTH       CAR_LANE_WIDTH        /**< Car width equals one lane. */
#define CAR_HEIGHT      TRACK_TILE_HEIGHT     /**< Car height equals one tile height. */
/** @} */

#define CAR_INITIAL_LIVES 3 /**< Default number of lives at session start. */

/**
 * @brief Four visual/health states of a car.
 *
 * The index maps directly to the sprite loaded by the View layer.
 */
#define CAR_PLAYER_COUNT 2 /**< Number of players (P1 + P2). */

typedef enum {
    CAR_STATE_NORMAL   = 0, /**< Car in perfect condition. */
    CAR_STATE_DAMAGED  = 1, /**< First impact — visible damage. */
    CAR_STATE_BURNING  = 2, /**< Second impact — on fire. */
    CAR_STATE_EXPLODED = 3, /**< Third impact — out of the race. */
    CAR_STATE_COUNT         /**< Sentinel — number of car states. */
} CarState;

/**
 * @brief Represents a player-controlled car.
 */
typedef struct {
    Element base;           /**< Position, hitbox, active flag, and sprite. */
    int     player;         /**< Player number: 1 or 2. */
    int     lane;           /**< Current logical lane index. */
    int     lane_min;       /**< Leftmost lane this car may occupy. */
    int     lane_max;       /**< Rightmost lane this car may occupy. */
    int     track_progress; /**< Logical rows completed (higher = further ahead). */
    float   boost_remaining;/**< Pixels remaining in the boost forward-animation (car moves up while > 0). */
    CarState state;         /**< Current damage/visual state. */
    int     score;          /**< Accumulated score for this session. */
    int     lives;          /**< Lives remaining; reaches 0 on EXPLODED. */
    bool    exploding;      /**< Endurance: true while the car is animating off-screen. */
    int     shield_ticks;   /**< Remaining invulnerability ticks (0 = no shield). */
} Car;

/**
 * @brief Allocates and initialises a Car.
 * @param initial_lane Starting lane index.
 * @param lane_min     Leftmost lane the car may use.
 * @param lane_max     Rightmost lane the car may use.
 * @param car_width    Width of the car hitbox in pixels.
 * @param car_height   Height of the car hitbox in pixels.
 * @return Pointer to the new Car, or NULL on allocation failure.
 */
Car* create_car(int initial_lane, int lane_min, int lane_max, int car_width, int car_height);

/**
 * @brief Frees a Car.
 * @param car Car to destroy.
 */
void destroy_car(Car *car);

/**
 * @brief Moves the car one lane sideways.
 * @param car       Car to move.
 * @param direction -1 to move left, +1 to move right.
 */
void car_move_lane(Car *car, int direction);

/**
 * @brief Advances the car's damage state by one step.
 *
 * Progresses NORMAL → DAMAGED → BURNING → EXPLODED and decrements lives.
 * @param car Car to damage.
 */
void car_take_damage(Car *car);

/**
 * @brief Instantly advances track progress by the given number of tiles (boost effect).
 * @param car   Car to boost.
 * @param tiles Number of logical rows to skip forward.
 */
void car_apply_boost(Car *car, int tiles);

/**
 * @brief Slides the car one lane in a random direction (banana-peel effect).
 * @param car Car to slip.
 */
void car_banana_slip(Car *car);

/**
 * @brief Resets the car to its initial position and CAR_STATE_NORMAL.
 * @param car          Car to reset.
 * @param initial_lane Lane to place the car on.
 */
void reset_car(Car *car, int initial_lane);

/**
 * @brief Initialises the score and life counter for a new game session.
 * @param car           Car to initialise.
 * @param initial_lives Number of lives to grant.
 */
void car_init_session(Car *car, int initial_lives);

/**
 * @brief Activates the shield for the given number of ticks.
 * @param car   Car to shield.
 * @param ticks Duration in game ticks (use SHIELD_DURATION_TICKS for 5 s).
 */
void car_apply_shield(Car *car, int ticks);

/**
 * @brief Converts a logical lane index to an X pixel coordinate.
 * @param lane Lane index (0-based).
 * @return X position of the lane's left edge in pixels.
 */
static inline double car_lane_to_x(int lane) {
    return (double)(lane * CAR_LANE_WIDTH);
}

#endif /* CAR_H */
