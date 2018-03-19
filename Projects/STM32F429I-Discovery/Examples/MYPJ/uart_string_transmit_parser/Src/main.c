#include "system_initialization.h"
#include "uart_printf.h"
#include "main.h"
#include "uart_string_transmit_parser.h"
#include "api_define.h"
#ifdef UART3
#include "uart3.h"
#elif UART6
#include "uart6.h"
#endif


int main(void)
{
	system_initialization();
	uart_printf_init();
#ifdef UART3
	struct uart_api *uart = (struct uart_api *)uart3_binding();
#elif UART6
	struct uart_api *uart = (struct uart_api *)uart6_binding();
#endif
	uart->init();
		
	transmit_pzem_voltage(uart);
	transmit_at_uart(uart);
}
