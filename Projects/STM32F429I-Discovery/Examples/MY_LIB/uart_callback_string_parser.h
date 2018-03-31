#ifndef __UART_CALLBACK_STRING_PARSER_H
#define __UART_CALLBACK_STRING_PARSER_H

#include "stm32f4xx_hal.h"

#define string_out_buffer_length 100

extern uint8_t uart_callback_string_byte; //for uart->receive_it() use between this.c and main.c

void uart_callback_parser(void);          //for HAL_UART_RxCpltCallback() use in uart_callback.c
uint8_t* uart_callback_string_out(void);
//Note: The length of once received packet cannot exceed 150 bytes


#endif
