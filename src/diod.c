#include "peripherals/gpio.h"
#include "utils.h"

void diod_init() {
    unsigned int selector;

    selector = get32(GPFSEL1);
    selector &= ~(7 << 18);                   // clean gpio16
	selector |= 1 << 18;                      // set output for gpio16
    put32(GPFSEL1, selector);
}

void diod_enable() {
    put32(GPSET0, (1 << 16));
}

void diod_disable() {
    put32(GPCLR0, (1 << 16));
}