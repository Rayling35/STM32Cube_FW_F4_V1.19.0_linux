#include <string.h>
#include "uart_callback_string_parser.h"
#include "api_define.h"
#include "uart_callback.h"
#include "uart3.h"
#include "uart6.h"
#include "uart7.h"


uint8_t uart_callback_string_byte; //extern data

static uint8_t string_out[string_out_buffer_length];
static uint8_t buffer_flag;

void uart_callback_parser(void)
{
#ifdef UART3_IT
	struct uart_api *uart3 = (struct uart_api *)uart3_binding();
#elif UART6_IT
	struct uart_api *uart6 = (struct uart_api *)uart6_binding();
#elif UART7_IT
	struct uart_api *uart7 = (struct uart_api *)uart7_binding();
#endif
	static uint8_t buffer[string_out_buffer_length];
	static uint16_t i = 0;
	
	buffer[i] = uart_callback_string_byte;
	i++;
	if(uart_callback_string_byte == 0x0A  &&  buffer[i-2] == 0x0D) {
		memset((char *)string_out, '\0', string_out_buffer_length);
		memcpy((char *)string_out, buffer, i-1);
		buffer_flag = 1;
		i = 0;
	}
#ifdef UART3_IT
	uart3->receive_it(&uart_callback_string_byte, 1);
	uart3_rx_callbake_flag = SET;
#elif UART6_IT
	uart6->receive_it(&uart_callback_string_byte, 1);
	uart6_rx_callbake_flag = SET;
#elif UART7_IT
	uart7->receive_it(&uart_callback_string_byte, 1);
	uart7_rx_callbake_flag = SET;
#endif
}

uint8_t* uart_callback_string_out(void)
{
	if(buffer_flag) {
		buffer_flag = 0;
		return string_out;
	}
	return NULL;
}
