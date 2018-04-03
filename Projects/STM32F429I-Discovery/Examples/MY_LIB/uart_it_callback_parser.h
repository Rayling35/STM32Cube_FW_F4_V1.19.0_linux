#ifndef __UART_IT_CALLBACK_PARSER_H
#define __UART_IT_CALLBACK_PARSER_H

#include "stm32f4xx_hal.h"
#include "api_define.h"


extern uint8_t uart_it_callback_string_byte;         //for uart->receive_it() use between this.c and main.c
void uart_it_callback_parser(struct uart_api *uart); //for HAL_UART_RxCpltCallback() use in uart_callback.c

#define it_string_out_buffer_length 100     //0x0D 0x0A
uint8_t* uart_it_callback_string_out(void); //The length of once received packet cannot exceed 150 bytes


#endif
