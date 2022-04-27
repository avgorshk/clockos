#include "mini_uart.h"
#include "utils.h"

void kernel_main(void)
{
	uart_init();

	while (1) {
		char symbol = uart_recv();
		if (symbol == 'c') {
			uart_send_string("Hello, world!\r\n");	
		}
	}
}
