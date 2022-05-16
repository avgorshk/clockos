#include "peripherals/gpio.h"
#include "utils.h"

void hour_button_init() {
    unsigned int selector;

    selector = get32(GPFSEL2);
    selector &= (~(7 << 3));                   // clean gpio21 -> input
    put32(GPFSEL2, selector);
}

unsigned hour_button_check() {
    unsigned int lev0 = get32(GPLEV0);
    return ((lev0 >> 21) & 1) == 0;
}