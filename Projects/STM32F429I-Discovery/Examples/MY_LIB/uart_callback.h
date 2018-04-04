#ifndef __UART_CALLBACK_H
#define __UART_CALLBACK_H

#include "stm32f4xx_hal.h"


#ifdef UART3_IT
extern __IO FlagStatus uart3_rx_callbake_flag;
#endif

#ifdef UART6_IT
extern __IO FlagStatus uart6_rx_callbake_flag;
#endif

#ifdef UART7_IT
extern __IO FlagStatus uart7_rx_callbake_flag;
#endif

#define UART3_IT_CALLBACK_PARSER(x)         uart_it_callback_parser(x)
#define UART6_IT_CALLBACK_PARSER(x)         uart_it_callback_parser(x)
#define UART7_IT_CALLBACK_PARSER(x)         uart_it_callback_parser(x)

#define UART3_DMA_CALLBACK_PARSER(x)        uart_dma1_callback_parser(x)
#define UART6_DMA_CALLBACK_PARSER(x)        uart_dma2_callback_parser(x)
#define UART7_DMA_CALLBACK_PARSER(x)        uart_dma3_callback_parser(x)


#endif
