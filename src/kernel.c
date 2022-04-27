#include "mini_uart.h"
#include "str_utils.h"
#include "watch.h"
#include "utils.h"

void print_time(Watch* watch) {
    char hour_str[MAX_STR_SIZE];
    char minute_str[MAX_STR_SIZE];
    char second_str[MAX_STR_SIZE];

    unsigned hour = watch_get_hour(watch);
    unsigned minute = watch_get_minute(watch);
    unsigned second = watch_get_second(watch);

    u32_to_str(hour, hour_str);
    u32_to_str(minute, minute_str);
    u32_to_str(second, second_str);

    uart_send_string(hour_str);
    uart_send(':');
    uart_send_string(minute_str);
    uart_send(':');
    uart_send_string(second_str);
    uart_send('\r');
    uart_send('\n');
}

void kernel_main(void) {
    Watch watch = watch_init();
    uart_init();

    while (1) {
        char symbol = uart_recv();
        switch (symbol) {
            case 'p':
                watch_update(&watch);
                print_time(&watch);
                break;
            case 'h':
                watch_inc_hour(&watch);
                print_time(&watch);
                break;
            case 'm':
                watch_inc_minute(&watch);
                print_time(&watch);
                break;
            default:
                break;
        }
    }
}
