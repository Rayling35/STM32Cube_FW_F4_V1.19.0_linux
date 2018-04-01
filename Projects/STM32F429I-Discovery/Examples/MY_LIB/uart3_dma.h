#ifndef __UART3_DMA_H
#define __UART3_DMA_H

#ifdef UART3_DMA
#define DMA_UART3_CLK_ENABLE()          __HAL_RCC_DMA1_CLK_ENABLE()

#define DMA_UART3_TX_STREAM             DMA1_Stream3
#define DMA_UART3_RX_STREAM             DMA1_Stream1
#define DMA_UART3_TX_CHANNEL            DMA_CHANNEL_4
#define DMA_UART3_RX_CHANNEL            DMA_CHANNEL_4

#define DMA_UART3_TX_IRQn               DMA1_Stream3_IRQn
#define DMA_UART3_RX_IRQn               DMA1_Stream1_IRQn
#define DMA_UART3_TX_IRQHandler         DMA1_Stream3_IRQHandler
#define DMA_UART3_RX_IRQHandler         DMA1_Stream1_IRQHandler


void _DMA_UART3_MspInit(void); //for HAL_UART_MspInit() use in uart_callback.c
void _DMA_UART3_MspDeInit(void); //for HAL_UART_MspDeInit() use in uart_callback.c

void DMA_UART3_TX_IRQHandler(void);
void DMA_UART3_RX_IRQHandler(void);
#endif

#endif
