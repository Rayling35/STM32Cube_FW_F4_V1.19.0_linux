#include <string.h>
#include "uart_callback_string_parser.h"
#include "api_define.h"
#include "uart_callback.h"
#include "uart7.h"


#ifdef IT_CALLBACK_PARSER
uint8_t uart_callback_string_byte;
uint8_t buffer_flag;

static uint8_t buffer[37];
struct_ble_cmd_data cmd_data;

void uart_callback_string_parser(void)
{
	struct uart_api *uart7 = (struct uart_api *)uart7_binding();
	static uint16_t i = 0;
	
	buffer[i] = uart_callback_string_byte;
	i++;
	if(i >= 37) {
		memcpy((char *)&cmd_data, buffer, 37);
		memset((char *)buffer, '\0', 37);
		i = 0;
		buffer_flag = 1;
	}
	uart7->receive_it(&uart_callback_string_byte, 1);
	uart7_rx_callbake_flag = SET;
}

struct_ble_cmd_data* get_data(void)
{
	if(buffer_flag) {
		buffer_flag = 0;
		return &cmd_data;
	}
	return NULL;
}
#endif
