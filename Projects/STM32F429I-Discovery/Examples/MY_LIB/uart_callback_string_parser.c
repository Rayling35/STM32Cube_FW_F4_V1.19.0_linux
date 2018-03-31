#include <string.h>
#include "uart_callback_string_parser.h"
#include "api_define.h"
#include "uart_callback.h"
#include "uart7.h"


uint8_t uart_callback_string_byte; //extern data

static uint8_t string_out[string_out_buffer_length];
static uint8_t buffer_flag;

void uart_callback_parser(void)
{
	struct uart_api *uart7 = (struct uart_api *)uart7_binding();
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
	uart7->receive_it(&uart_callback_string_byte, 1);
	uart7_rx_callbake_flag = SET;
}

uint8_t* uart_callback_string_out(void)
{
	if(buffer_flag) {
		buffer_flag = 0;
		return string_out;
	}
	return NULL;
}
