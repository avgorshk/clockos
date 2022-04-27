#ifndef _WATCH_H
#define _WATCH_H

typedef struct __Watch {
    unsigned hour;
    unsigned minute;
    unsigned second;

    unsigned base_hour;
    unsigned base_minute;

    unsigned long long timer;
} Watch;

Watch watch_init();
void watch_update(Watch* watch);
void watch_inc_hour(Watch* watch);
void watch_inc_minute(Watch* watch);
unsigned watch_get_hour(Watch* watch);
unsigned watch_get_minute(Watch* watch);
unsigned watch_get_second(Watch* watch);

#endif /* _WATCH_H */