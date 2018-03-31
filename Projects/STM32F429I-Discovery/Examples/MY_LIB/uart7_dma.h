#ifndef __UART7_DMA_H
#define __UART7_DMA_H

#define DMA_UART7_CLK_ENABLE()          __HAL_RCC_DMA1_CLK_ENABLE()

#define DMA_UART7_TX_STREAM             DMA1_Stream1
#define DMA_UART7_RX_STREAM             DMA1_Stream3
#define DMA_UART7_TX_CHANNEL            DMA_CHANNEL_5
#define DMA_UART7_RX_CHANNEL            DMA_CHANNEL_5

#define DMA_UART7_TX_IRQn               DMA1_Stream1_IRQn
#define DMA_UART7_RX_IRQn               DMA1_Stream3_IRQn
#define DMA_UART7_TX_IRQHandler         DMA1_Stream1_IRQHandler
#define DMA_UART7_RX_IRQHandler         DMA1_Stream3_IRQHandler


void _DMA_UART7_MspInit(void); //for HAL_UART_MspInit() use in uart_callback.c
void _DMA_UART7_MspDeInit(void); //for HAL_UART_MspDeInit() use in uart_callback.c

void DMA_UART7_TX_IRQHandler(void);
void DMA_UART7_RX_IRQHandler(void);

#endif
