#ifndef __UART_IT_CALLBACK_PARSER_H
#define __UART_IT_CALLBACK_PARSER_H

#include "api_define.h"


/* UART3 */
extern uint8_t uart_it1_callback_string_byte;         //for uart->receive_it() use between this.c and main.c
void uart_it1_callback_parser(struct uart_api *uart); //for HAL_UART_RxCpltCallback() use in uart_callback.c

#define it1_string_out_buffer_length 1
uint8_t* uart_it1_callback_string_out(void);


/* UART6 */
extern uint8_t uart_it2_callback_string_byte;         //for uart->receive_it() use between this.c and main.c
void uart_it2_callback_parser(struct uart_api *uart); //for HAL_UART_RxCpltCallback() use in uart_callback.c

#define it2_string_out_buffer_length 100     //0x0D 0x0A
uint8_t* uart_it2_callback_string_out(void);


/* UART7 */
extern uint8_t uart_it3_callback_string_byte;         //for uart->receive_it() use between this.c and main.c
void uart_it3_callback_parser(struct uart_api *uart); //for HAL_UART_RxCpltCallback() use in uart_callback.c

#define it3_string_out_buffer_length 100     //0x0D 0x0A
uint8_t* uart_it3_callback_string_out(void);


#endif
