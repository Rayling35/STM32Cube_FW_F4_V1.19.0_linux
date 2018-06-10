/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include <string.h>
#include "stm32f4xx_hal.h"
#include "api_define.h"
#include "uart_string_transmit_parser.h"


int pzem_data_send(struct uart_api *huart, pzem004t_data_t *data)
{
	huart->transmit((uint8_t *)data, 7, 1000);
	return 0;
}

int uart_at_command(struct uart_api *huart, uat_data_t *data)
{
	char buffer[] = "\0";
	
	sprintf(buffer, "%s+%s=%d,%d,%d", data->command, data->device, data->data1, data->data2, data->data3);
	huart->transmit((uint8_t *)buffer, strlen(buffer), 1000);
	return 0;
}
