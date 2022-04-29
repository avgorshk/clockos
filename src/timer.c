#include "diod.h"
#include "printf.h"
#include "peripherals/timer.h"
#include "utils.h"

unsigned int hour = 0;
unsigned int minute = 0;
unsigned int second = 0;

const unsigned int interval = 1000000; // 1 second
unsigned int curVal = 0;

void timer_init( void )
{
	curVal = get32(TIMER_CLO);
	curVal += interval;
	put32(TIMER_C1, curVal);

	diod_init();
}

void timer_print() {
	printf("%02u:%02u:%02u\r\n", hour, minute, second);
}

void timer_inc_hour() {
	hour += 1;
	hour %= 24;
}

void timer_inc_minute() {
	minute += 1;
	if (minute == 60) {
		minute = 0;
		timer_inc_hour();
	}
}

void timer_inc_second() {
	second += 1;
	if (second == 60) {
		second = 0;
		timer_inc_minute();
	}
}

void timer_add_hour() {
	hour += 1;
	hour %= 24;
	second = 0;
}

void timer_add_minute() {
	minute += 1;
	minute %= 60;
	second = 0;
}

void handle_timer_irq( void )
{
	curVal += interval;
	put32(TIMER_C1, curVal);
	put32(TIMER_CS, TIMER_CS_M1);

	timer_inc_second();
	if ((second & 1) == 0) {
		diod_enable();
	} else {
		diod_disable();
	}

	timer_print();
}
