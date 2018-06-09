/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
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

	uint8_t buffer[50];
	
	head_checkout(uart, "GPABCD", buffer, 50);
	gps_data_t *gps = a_parser(buffer);
	printf("START = %s\r\n", gps->start);

/*---------------------------------------------------------*/
	char name[] = {0x0A,0x41};
	head_checkout(uart, name, buffer, 50);
	version_data_t *version = version_parser(buffer);
	
	char region[5];
	int re;
	sprintf(region, "%.5s\r\n", version->region);
	re = strtol(region, NULL, 16);
	printf("region %d\r\n", re);
}
