#include <string.h>
#include "uart_it_callback_parser.h"
#include "api_define.h"
#include "uart_callback.h"
#include "uart3.h"
#include "uart6.h"
#include "uart7.h"


uint8_t uart_it_callback_string_byte; //extern data

static uint8_t string_out[it_string_out_buffer_length];
static uint8_t buffer_flag = 0;

void uart_it_callback_parser(void)
{
#ifdef IT_CALLBACK_PARSER_U3
	struct uart_api *uart3 = (struct uart_api *)uart3_binding();
#elif IT_CALLBACK_PARSER_U6
	struct uart_api *uart6 = (struct uart_api *)uart6_binding();
#elif IT_CALLBACK_PARSER_U7
	struct uart_api *uart7 = (struct uart_api *)uart7_binding();
#endif
	static uint8_t buffer[it_string_out_buffer_length];
	static uint16_t i = 0;
	
	buffer[i] = uart_it_callback_string_byte;
	i++;
	if(uart_it_callback_string_byte == 0x0A  &&  buffer[i-2] == 0x0D) {
		memset((char *)string_out, '\0', it_string_out_buffer_length);
		memcpy((char *)string_out, buffer, i-1);
		buffer_flag = 1;
		i = 0;
	}
#ifdef IT_CALLBACK_PARSER_U3
	uart3->receive_it(&uart_it_callback_string_byte, 1);
	uart3_rx_callbake_flag = SET;
#elif IT_CALLBACK_PARSER_U6
	uart6->receive_it(&uart_it_callback_string_byte, 1);
	uart6_rx_callbake_flag = SET;
#elif IT_CALLBACK_PARSER_U7
	uart7->receive_it(&uart_it_callback_string_byte, 1);
	uart7_rx_callbake_flag = SET;
#endif
}

int uart_it_callback_string_out(uint8_t *out)
{
	if(buffer_flag) {
		buffer_flag = 0;
		memcpy((char *)out, string_out, it_string_out_buffer_length);
		if(buffer_flag) {
			return 1;
		}else {
			return 0;
		}
	}
	return NULL;
}
