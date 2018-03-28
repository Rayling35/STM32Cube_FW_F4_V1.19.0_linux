#ifndef __UART_CALLBACK_STRING_PARSER_H
#define __UART_CALLBACK_STRING_PARSER_H

#include "stm32f4xx_hal.h"

extern uint8_t uart_callback_string_byte; //for uart->receive_it() use

typedef struct {
	char start[6]; //GPABCD
	char o1[1];    //,
	char data1[1]; //T
	char o2[1];    //,
	char data2[2]; //QW
	char o3[1];    //,
	char data3[3]; //Y22
	char o4[1];    //,
	char data4[4]; //56tr
	char o5[1];    //,
	char data5[5]; //S23_E
	char o6[1];    //,
	char data6[6]; //KK2341
	char o7[1];    //,
	char end[3];   //Off
}struct_ble_cmd_data;
//GPABCD,T,QW,Y22,56tr,S23_E,KK2341,Off


void uart_callback_string_parser(void); //for HAL_UART_RxCpltCallback() in uart_callback.c
struct_ble_cmd_data* get_data(void);


#endif
