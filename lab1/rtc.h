#ifndef RTC_H
#define RTC_H

#include <stdint.h>

#define RTC_ADDR_REG  0x70
#define RTC_DATA_REG  0x71

#define RTC_REG_A     0x0A
#define RTC_REG_B     0x0B

#define RTC_REG_SEC   0x00
#define RTC_REG_MIN   0x02
#define RTC_REG_HOUR  0x04
#define RTC_REG_DAY   0x07
#define RTC_REG_MONTH 0x08
#define RTC_REG_YEAR  0x09

#define RTC_UIP_MSK   (1 << 7)
#define RTC_DM_MSK    (1 << 2)

typedef struct {
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
} rtc_time;

typedef struct {
    uint8_t day;
    uint8_t month;
    uint8_t year;
} rtc_date;

int rtc_read_date(rtc_date *date);
int rtc_read_time(rtc_time *time);

#endif /* RTC_H */
