#ifndef __UART_DMA_CALLBACK_PARSER_H
#define __UART_DMA_CALLBACK_PARSER_H

#include "stm32f4xx_hal.h"

/* UART3 */
extern uint8_t uart_dma1_callback_string_byte; //for uart->receive_dma() use between this.c and main.c
void uart_dma1_callback_parser(void);          //for HAL_UART_RxCpltCallback() use in uart_callback.c

#define dma1_string_out_buffer_length 100      //0x0D 0x0A end
int uart_dma1_callback_string_out(uint8_t *out);
//Note: The length of once received packet cannot exceed 150 bytes


/* UART6 */
extern uint8_t uart_dma2_callback_string_byte; //for uart->receive_dma() use between this.c and main.c
void uart_dma2_callback_parser(void);          //for HAL_UART_RxCpltCallback() use in uart_callback.c

#define dma2_string_out_buffer_length 100      //0x0D 0x0A end
int uart_dma2_callback_string_out(uint8_t *out);
//Note: The length of once received packet cannot exceed 150 bytes


/* UART7 */
extern uint8_t uart_dma3_callback_string_byte; //for uart->receive_dma() use between this.c and main.c
void uart_dma3_callback_parser(void);          //for HAL_UART_RxCpltCallback() use in uart_callback.c

#define dma3_string_out_buffer_length 100      //0x0D 0x0A end
int uart_dma3_callback_string_out(uint8_t *out);
//Note: The length of once received packet cannot exceed 150 bytes


#endif
