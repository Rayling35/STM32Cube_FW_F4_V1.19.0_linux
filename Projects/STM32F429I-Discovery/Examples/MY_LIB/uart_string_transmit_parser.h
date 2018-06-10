/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#ifndef __UART_STRING_TRANSMIT_PARSER_H
#define __UART_STRING_TRANSMIT_PARSER_H

#include "api_define.h"


typedef struct {
	uint8_t head;
	uint8_t data1;
	uint8_t data2;
	uint8_t data3;
	uint8_t data4;
	uint8_t data5;
	uint8_t sum;
}pzem004t_data_t;

typedef struct {
	char *command;
	char *device;
	int data1;
	int data2;
	int data3;
}uat_data_t;

int pzem_data_send(struct uart_api *huart, pzem004t_data_t *data);
int uart_at_command(struct uart_api *huart, uat_data_t *data);


#endif
