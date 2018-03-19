#include <stdlib.h>
#include "system_initialization.h"
#include "uart_printf.h"
#include "main.h"
#include "uart_string_receive_parser.h"
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

	uint8_t rx_buffer[50];
	
	struct receive_table_a *a;
	a = (struct receive_table_a*)rx_buffer;
	receive_cmd_a(uart, rx_buffer, 50);
	a_parser(rx_buffer);
	
	printf("START = %s\r\n", a->start);

/*---------------------------------------------------------*/
	struct receive_table_version *version;
	version = (struct receive_table_version*)rx_buffer;
	receive_cmd_version(uart, rx_buffer, 50);
	version_parser(rx_buffer);
	
	char region[5];
	int re;
	sprintf(region, "%.5s\r\n", version->region);
	re = strtol(region, NULL, 16);
	printf("region %d\r\n", re);
}
