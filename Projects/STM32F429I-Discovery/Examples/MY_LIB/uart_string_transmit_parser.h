#ifndef __UART_STRING_TRANSMIT_PARSER_H
#define __UART_STRING_TRANSMIT_PARSER_H

#include "stm32f4xx_hal.h"
#include "api_define.h"


typedef struct {
	uint8_t head;
	uint8_t data1;
	uint8_t data2;
	uint8_t data3;
	uint8_t data4;
	uint8_t data5;
	uint8_t sum;
}struct_pzem004t_data;

typedef struct {
	char *command;
	char *device;
	int data1;
	int data2;
	int data3;
}struct_uat_data;


int pzem_data_send(struct uart_api *huart, struct_pzem004t_data *data);
int uart_at_command(struct uart_api *huart, struct_uat_data *data);


#endif
