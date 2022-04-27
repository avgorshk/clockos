#include "utils.h"
#include "peripherals/sys_timer.h"

unsigned sys_timer_read_low() {
    return get32(CLO_REG);
}

unsigned sys_timer_read_high() {
    return get32(CHI_REG);
}

unsigned long long sys_timer_read() {
    unsigned low = sys_timer_read_low();
    unsigned high = sys_timer_read_high();
    unsigned long long timer = high;
    timer <<= 32;
    timer += low;
    return timer;
}