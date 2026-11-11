#include "leaderboard.h"
#include "rtc.h"
#include <string.h>

static Leaderboard lb;

void leaderboard_read_rtc(int *hour, int *min, int *sec) {
    rtc_time t;
    if (rtc_read_time(&t) != 0) {
        *hour = 0; *min = 0; *sec = 0;
        return;
    }
    *hour = t.hour;
    *min  = t.minute;
    *sec  = t.second;
}

void leaderboard_init(void) {
    lb.count = 0;
    memset(lb.entries, 0, sizeof(lb.entries));
}

void leaderboard_add(const char *player, int race_time_sec,
                     int rtc_hour, int rtc_min, int rtc_sec) {
    LeaderboardEntry entry;
    strncpy(entry.player, player, 7);
    entry.player[7]     = '\0';
    entry.race_time_sec = race_time_sec;
    entry.rtc_hour      = rtc_hour;
    entry.rtc_min       = rtc_min;
    entry.rtc_sec       = rtc_sec;

    rtc_date d;
    if (rtc_read_date(&d) == 0) {
        entry.rtc_day   = d.day;
        entry.rtc_month = d.month;
    } else {
        entry.rtc_day   = 0;
        entry.rtc_month = 0;
    }

    if (lb.count < MAX_LEADERBOARD) {
        lb.count++;
    } else {
        /* Full — only insert if this score beats the current worst entry. */
        if (entry.race_time_sec <= lb.entries[MAX_LEADERBOARD - 1].race_time_sec)
            return;
    }

    /* Place at the end, then bubble up into sorted position (descending). */
    int i = lb.count - 1;
    lb.entries[i] = entry;
    while (i > 0 && lb.entries[i].race_time_sec > lb.entries[i - 1].race_time_sec) {
        LeaderboardEntry tmp  = lb.entries[i];
        lb.entries[i]         = lb.entries[i - 1];
        lb.entries[i - 1]     = tmp;
        i--;
    }
}

Leaderboard *leaderboard_get(void) {
    return &lb;
}

int leaderboard_get_count(void) {
    return lb.count;
}
