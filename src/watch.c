#include "watch.h"
#include "sys_timer.h"

// DBG
#include "mini_uart.h"
#include "str_utils.h"
// DBG

#define SYS_TIMER_FREQ 1000000
#define SEC_IN_MIN     60
#define SEC_IN_HOUR    3600

Watch watch_init() {
    Watch watch;
    watch.hour = 0;
    watch.minute = 0;
    watch.second = 0;
    watch.base_hour = 0;
    watch.base_minute = 0;
    watch.timer = sys_timer_read();
    return watch;
}

void watch_update_hour(Watch* watch, unsigned hours) {
    watch->hour += hours;
    watch->hour %= 24;
}

void watch_update_minute(Watch* watch, unsigned minutes) {
    watch->minute += minutes;
    if (watch->minute >= 60) {
        watch->minute -= 60;
        watch_update_hour(watch, 1);
    }
}

void watch_update(Watch* watch) {
    unsigned long long current_timer = sys_timer_read();
    unsigned long long start_timer = watch->timer;
    unsigned long long diff_sec = (current_timer - start_timer) / SYS_TIMER_FREQ;

    unsigned hours = diff_sec / SEC_IN_HOUR;
    diff_sec -= hours * SEC_IN_HOUR;
    watch->hour = (hours % 24);
    watch_update_hour(watch, watch->base_hour);

    unsigned minutes = diff_sec / SEC_IN_MIN;
    diff_sec -= minutes * SEC_IN_MIN;
    watch->minute = minutes;
    watch_update_minute(watch, watch->base_minute);

    unsigned seconds = diff_sec;
    watch->second = seconds;
}

void watch_inc_hour(Watch* watch) {
    watch->base_hour += 1;
    watch->base_hour %= 24;
    watch->timer = sys_timer_read();
    watch_update(watch);
}

void watch_inc_minute(Watch* watch) {
    watch->base_minute += 1;
    watch->base_minute %= 60;
    watch->timer = sys_timer_read();
    watch_update(watch);
}

unsigned watch_get_hour(Watch* watch) {
    return watch->hour;
}

unsigned watch_get_minute(Watch* watch) {
    return watch->minute;
}

unsigned watch_get_second(Watch* watch) {
    return watch->second;
}