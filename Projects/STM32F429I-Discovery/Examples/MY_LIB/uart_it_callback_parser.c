#include <string.h>
#include "uart_it_callback_parser.h"


uint8_t uart_it_callback_string_byte; //extern data

static uint8_t string_out[it_string_out_buffer_length];
static uint8_t buffer_flag = 0;

void uart_it_callback_parser(struct uart_api *uart)
{
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
	uart->receive_it(&uart_it_callback_string_byte, 1);
}

uint8_t* uart_it_callback_string_out(void)
{
	if(buffer_flag) {
		buffer_flag = 0;
		return string_out;
	}
	return NULL;
}
