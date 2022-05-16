#include "printf.h"
#include "timer.h"
#include "irq.h"
#include "mini_uart.h"
#include "utils.h"

#include "minute_button.h"
#include "hour_button.h"

void kernel_main(void)
{
	uart_init();
	init_printf(0, putc);
	irq_vector_init();
	timer_init();
	minute_button_init();
	hour_button_init();
	enable_interrupt_controller();
	enable_irq();

	while (1) {
		/*switch (uart_recv()) {
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
		}*/
		if (minute_button_check()) {
			timer_add_minute();
			printf("-->");
			timer_print();
		}
		if (hour_button_check()) {
			timer_add_hour();
			printf("-->");
			timer_print();
		}
	}
}
