#ifndef __UART_STRING_RECEIVE_PARSER_H
#define __UART_STRING_RECEIVE_PARSER_H

#include "stm32f4xx_hal.h"
#include <string.h>
#include <stdlib.h>

struct receive_table_a {
	char start[6];
	char o1[1];
	char data1[10];
	char o2[1];
	char data2[10];
	char o3[1];
	char data3[1];
	char o4[1];
	char data4[11];
	char o5[1];
	char data5[1];
	char o6[1];
	char data6[1];
	char o7[1];
	char data7[2];
	char o8[1];
	char data8[4];
	char o9[1];
	char data9[6];
	char o10[1];
	char data10[1];
	char o11[1];
	char data11[3];
	char o12[1];
	char data12[1];
	char o13[1];
	char data13[1];
	char o14[1];
	char end[3];
	char o15[1];
};

struct receive_table_version {
	char start[1];
	char cmd[1];
	char ver1[10];
	char o1[1];
	char id[10];
	char o2[1];
	char ver2[10];
	char o3[1];
	char region[10];
	char end[2];
	char o4[1];
};

uint16_t receive_cmd_a(UART_HandleTypeDef *huart, uint8_t *buffer, uint16_t length);
uint16_t receive_cmd_version(UART_HandleTypeDef *huart, uint8_t *buffer, uint16_t length);

#endif
