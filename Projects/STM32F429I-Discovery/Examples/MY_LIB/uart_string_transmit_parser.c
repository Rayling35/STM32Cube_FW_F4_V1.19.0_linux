#include <string.h>
#include "uart_string_transmit_parser.h"


int pzem_data_send(struct uart_api *huart, struct_pzem004t_data *data)
{
	huart->transmit((uint8_t *)data, 7, 1000);
	return 0;
}

int uart_at_command(struct uart_api *huart, struct_uat_data *data)
{
	char buffer[] = "\0";
	
	sprintf(buffer, "%s+%s=%d,%d,%d", data->command, data->device, data->data1, data->data2, data->data3);
	huart->transmit((uint8_t *)buffer, strlen(buffer), 1000);
	return 0;
}
