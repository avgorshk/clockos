#include "peripherals/gpio.h"
#include "utils.h"

void minute_button_init() {
    unsigned int selector;

    selector = get32(GPFSEL2);
    selector &= (~7);                   // clean gpio20 -> input
    put32(GPFSEL2, selector);
}

unsigned minute_button_check() {
    unsigned int lev0 = get32(GPLEV0);
    return ((lev0 >> 20) & 1) == 0;
}