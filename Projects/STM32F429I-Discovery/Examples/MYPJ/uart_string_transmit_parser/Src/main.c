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
	
	struct_pzem004t_data pzem004t = {
	.head = 0xB0,
	.data1 = 0xC0,
	.data2 = 0xA8,
	.data3 = 0x01,
	.data4 = 0x01,
	.data5 = 0x00,
	.sum = (pzem004t.head + pzem004t.data1 +
					pzem004t.data2 + pzem004t.data3 +
					pzem004t.data4 + pzem004t.data5) & 0xFF,
	};
	pzem_data_send(uart, &pzem004t);
	
	/*---------------------------------------------------------*/
	struct_uat_data uat = {
	.command = "AT",
	.device = "UART",
	.data1 = 115200,
	.data2 = 0,
	.data3 = 1,
	};
	uart_at_command(uart, &uat);
}
