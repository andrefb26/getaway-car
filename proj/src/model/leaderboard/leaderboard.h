/**
 * @file leaderboard.h
 * @brief Session leaderboard: stores and ranks the top race results.
 */

#ifndef LEADERBOARD_H
#define LEADERBOARD_H

/** @brief Maximum number of entries kept in the leaderboard. */
#define MAX_LEADERBOARD 6

/**
 * @brief A single leaderboard entry recording the winner and session timestamp.
 */
typedef struct {
    char player[8];     /**< Winning player label: "RED" or "BLUE". */
    int  race_time_sec; /**< Race/survival duration in seconds. */
    int  rtc_day;       /**< RTC day when the race ended (1-31). */
    int  rtc_month;     /**< RTC month when the race ended (1-12). */
    int  rtc_hour;      /**< RTC hour when the race ended (0-23). */
    int  rtc_min;       /**< RTC minute when the race ended (0-59). */
    int  rtc_sec;       /**< RTC second when the race ended (0-59). */
} LeaderboardEntry;

/**
 * @brief Ranked collection of the top race results.
 */
typedef struct {
    LeaderboardEntry entries[MAX_LEADERBOARD]; /**< Entries sorted descending by race_time_sec. */
    int              count;                    /**< Number of valid entries (0-MAX_LEADERBOARD). */
} Leaderboard;

/**
 * @brief Initialises the global leaderboard to an empty state.
 */
void leaderboard_init(void);

/**
 * @brief Inserts a new result into the leaderboard.
 *
 * Entries are kept sorted in descending order of race_time_sec.
 * When the leaderboard is full the lowest-ranked entry is dropped if the
 * new result scores higher.
 *
 * @param player        Winning player label ("RED" or "BLUE").
 * @param race_time_sec Race duration in seconds.
 * @param rtc_hour      RTC hour at race end.
 * @param rtc_min       RTC minute at race end.
 * @param rtc_sec       RTC second at race end.
 */
void leaderboard_add(const char *player, int race_time_sec,
                     int rtc_hour, int rtc_min, int rtc_sec);

/**
 * @brief Returns a pointer to the global Leaderboard.
 * @return Non-NULL pointer; valid for the lifetime of the process.
 */
Leaderboard *leaderboard_get(void);

/**
 * @brief Returns the number of valid entries currently in the leaderboard.
 * @return Entry count in [0, MAX_LEADERBOARD].
 */
int leaderboard_get_count(void);

/**
 * @brief Reads the current time from the RTC hardware.
 *
 * Uses sys_outb/sys_inb on ports 0x70/0x71 and converts the result from
 * BCD to binary.
 *
 * @param hour  Output: current hour (0-23).
 * @param min   Output: current minute (0-59).
 * @param sec   Output: current second (0-59).
 */
void leaderboard_read_rtc(int *hour, int *min, int *sec);

#endif /* LEADERBOARD_H */
