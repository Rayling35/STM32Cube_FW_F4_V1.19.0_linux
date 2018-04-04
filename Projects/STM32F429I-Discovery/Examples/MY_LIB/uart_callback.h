#ifndef __UART_CALLBACK_H
#define __UART_CALLBACK_H


#define UART3_IT_CALLBACK_PARSER(x)         uart_it_callback_parser(x)
#define UART6_IT_CALLBACK_PARSER(x)         uart_it_callback_parser(x)
#define UART7_IT_CALLBACK_PARSER(x)         uart_it_callback_parser(x)

#define UART3_DMA_CALLBACK_PARSER(x)        uart_dma1_callback_parser(x)
#define UART6_DMA_CALLBACK_PARSER(x)        uart_dma2_callback_parser(x)
#define UART7_DMA_CALLBACK_PARSER(x)        uart_dma3_callback_parser(x)


#endif
