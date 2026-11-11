#include "rtc.h"
#include <minix/syslib.h>
#include <minix/sysutil.h>

static int rtc_read_reg(uint8_t reg, uint32_t *value) {
    if (sys_outb(RTC_ADDR_REG, reg) != 0) return 1;
    if (sys_inb(RTC_DATA_REG, value) != 0) return 1;
    return 0;
}

static int bcd_to_bin(uint8_t bcd) {
    return (bcd & 0x0F) + ((bcd >> 4) * 10);
}

static int is_updating() {
    uint32_t regA;
    if (rtc_read_reg(RTC_REG_A, &regA) != 0) return -1;
    return (regA & RTC_UIP_MSK) ? 1 : 0;
}

static int wait_not_updating() {
    int tries = 0;
    int updating;

    while ((updating = is_updating()) != 0) {
        if (updating == -1) return 1;
        if (++tries >= 50)  return 1;
        tickdelay(micros_to_ticks(20000));
    }

    return 0;
}

int rtc_read_date(rtc_date *date) {
    uint32_t regB, day, month, year;

    if (wait_not_updating() != 0) return 1;

    if (rtc_read_reg(RTC_REG_DAY,   &day)   != 0) return 1;
    if (rtc_read_reg(RTC_REG_MONTH, &month) != 0) return 1;
    if (rtc_read_reg(RTC_REG_YEAR,  &year)  != 0) return 1;
    if (rtc_read_reg(RTC_REG_B,     &regB)  != 0) return 1;

    if (!(regB & RTC_DM_MSK)) {
        day   = bcd_to_bin((uint8_t)day);
        month = bcd_to_bin((uint8_t)month);
        year  = bcd_to_bin((uint8_t)year);
    }

    date->day   = (uint8_t)day;
    date->month = (uint8_t)month;
    date->year  = (uint8_t)year;

    return 0;
}

int rtc_read_time(rtc_time *time) {
    uint32_t regB, hour, minute, second;

    if (wait_not_updating() != 0) return 1;

    if (rtc_read_reg(RTC_REG_HOUR, &hour)   != 0) return 1;
    if (rtc_read_reg(RTC_REG_MIN,  &minute) != 0) return 1;
    if (rtc_read_reg(RTC_REG_SEC,  &second) != 0) return 1;
    if (rtc_read_reg(RTC_REG_B,    &regB)   != 0) return 1;

    if (!(regB & RTC_DM_MSK)) {
        hour   = bcd_to_bin((uint8_t)hour);
        minute = bcd_to_bin((uint8_t)minute);
        second = bcd_to_bin((uint8_t)second);
    }

    time->hour   = (uint8_t)hour;
    time->minute = (uint8_t)minute;
    time->second = (uint8_t)second;

    return 0;
}
