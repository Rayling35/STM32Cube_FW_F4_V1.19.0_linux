#include <string.h>
#include "uart_callback_string_parser.h"
#include "api_define.h"
#include "uart_callback.h"
#include "uart7.h"


#ifdef IT_CALLBACK_PARSER
uint8_t uart_callback_string_byte; //extern data
static uint8_t buffer_flag;
static uint8_t string_out[100];

void uart_callback_parser(void)
{
	struct uart_api *uart7 = (struct uart_api *)uart7_binding();
	static uint8_t buffer[100];
	static uint16_t i = 0;
	
	buffer[i] = uart_callback_string_byte;
	i++;
	if(uart_callback_string_byte == 0x0A) {
		memcpy((char *)&string_out, buffer, 100);
		memset((char *)buffer, '\0', 100);
		i = 0;
		buffer_flag = 1;
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
#endif
