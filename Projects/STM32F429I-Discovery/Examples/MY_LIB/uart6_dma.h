#ifndef __UART6_DMA_H
#define __UART6_DMA_H

#ifdef UART6_DMA
#define DMA_UART6_CLK_ENABLE()          __HAL_RCC_DMA2_CLK_ENABLE()

#define DMA_UART6_TX_STREAM             DMA2_Stream6
#define DMA_UART6_RX_STREAM             DMA2_Stream1
#define DMA_UART6_TX_CHANNEL            DMA_CHANNEL_5
#define DMA_UART6_RX_CHANNEL            DMA_CHANNEL_5

#define DMA_UART6_TX_IRQn               DMA2_Stream6_IRQn
#define DMA_UART6_RX_IRQn               DMA2_Stream1_IRQn
#define DMA_UART6_TX_IRQHandler         DMA2_Stream6_IRQHandler
#define DMA_UART6_RX_IRQHandler         DMA2_Stream1_IRQHandler


void _DMA_UART6_MspInit(void); //for HAL_UART_MspInit() use in uart_callback.c
void _DMA_UART6_MspDeInit(void); //for HAL_UART_MspDeInit() use in uart_callback.c

void DMA_UART6_TX_IRQHandler(void);
void DMA_UART6_RX_IRQHandler(void);
#endif

#endif
