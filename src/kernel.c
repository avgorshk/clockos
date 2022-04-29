#include "printf.h"
#include "timer.h"
#include "irq.h"
#include "mini_uart.h"
#include "utils.h"

void kernel_main(void)
{
	uart_init();
	init_printf(0, putc);
	irq_vector_init();
	timer_init();
	enable_interrupt_controller();
	enable_irq();

	while (1) {
		switch (uart_recv()) {
			case 'h':
				timer_add_hour();
				printf("-->");
				timer_print();
				break;
			case 'm':
				timer_add_minute();
				printf("-->");
				timer_print();
				break;
			default:
				break;
		}
	}
}
