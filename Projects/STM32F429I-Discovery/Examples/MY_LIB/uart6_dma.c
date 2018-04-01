#include "stm32f4xx_hal.h"
#include "uart6_dma.h"
#include "uart6.h"
#include "api_define.h"


#ifdef UART6_DMA
static DMA_HandleTypeDef HdmaHandle_uart6_tx;
static DMA_HandleTypeDef HdmaHandle_uart6_rx;

void _DMA_UART6_MspInit(void)
{
	struct uart_api *uart6 = (struct uart_api *)uart6_binding();
	
	DMA_UART6_CLK_ENABLE();
	
	HdmaHandle_uart6_tx.Instance                 = DMA_UART6_TX_STREAM;
	HdmaHandle_uart6_tx.Init.Channel             = DMA_UART6_TX_CHANNEL;
	HdmaHandle_uart6_tx.Init.Direction           = DMA_MEMORY_TO_PERIPH;
	HdmaHandle_uart6_tx.Init.PeriphInc           = DMA_PINC_DISABLE;
	HdmaHandle_uart6_tx.Init.MemInc              = DMA_MINC_ENABLE;
	HdmaHandle_uart6_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	HdmaHandle_uart6_tx.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;
	HdmaHandle_uart6_tx.Init.Mode                = DMA_NORMAL;
	HdmaHandle_uart6_tx.Init.Priority            = DMA_PRIORITY_LOW;
	HdmaHandle_uart6_tx.Init.FIFOMode            = DMA_FIFOMODE_DISABLE;
	HdmaHandle_uart6_tx.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;
	HdmaHandle_uart6_tx.Init.MemBurst            = DMA_MBURST_INC4;
	HdmaHandle_uart6_tx.Init.PeriphBurst         = DMA_PBURST_INC4;
	HAL_DMA_Init(&HdmaHandle_uart6_tx);
	
	__HAL_LINKDMA(uart6->handle, hdmatx, HdmaHandle_uart6_tx);
	
	HdmaHandle_uart6_rx.Instance                 = DMA_UART6_RX_STREAM;
	HdmaHandle_uart6_rx.Init.Channel             = DMA_UART6_RX_CHANNEL;
	HdmaHandle_uart6_rx.Init.Direction           = DMA_PERIPH_TO_MEMORY;
	HdmaHandle_uart6_rx.Init.PeriphInc           = DMA_PINC_DISABLE;
	HdmaHandle_uart6_rx.Init.MemInc              = DMA_MINC_ENABLE;
	HdmaHandle_uart6_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	HdmaHandle_uart6_rx.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;
	HdmaHandle_uart6_rx.Init.Mode                = DMA_NORMAL;
	HdmaHandle_uart6_rx.Init.Priority            = DMA_PRIORITY_LOW;
	HdmaHandle_uart6_rx.Init.FIFOMode            = DMA_FIFOMODE_DISABLE;
	HdmaHandle_uart6_rx.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;
	HdmaHandle_uart6_rx.Init.MemBurst            = DMA_MBURST_INC4;
	HdmaHandle_uart6_rx.Init.PeriphBurst         = DMA_PBURST_INC4;
	HAL_DMA_Init(&HdmaHandle_uart6_rx);
	
	__HAL_LINKDMA(uart6->handle, hdmarx, HdmaHandle_uart6_rx);
	
	HAL_NVIC_SetPriority(DMA_UART6_TX_IRQn, 0, 1);
	HAL_NVIC_EnableIRQ(DMA_UART6_TX_IRQn);
	
	HAL_NVIC_SetPriority(DMA_UART6_RX_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(DMA_UART6_RX_IRQn);
}

void _DMA_UART6_MspDeInit(void)
{
	HAL_DMA_DeInit(&HdmaHandle_uart6_tx);
	HAL_DMA_DeInit(&HdmaHandle_uart6_rx);
	
	HAL_NVIC_DisableIRQ(DMA_UART6_TX_IRQn);
	HAL_NVIC_DisableIRQ(DMA_UART6_RX_IRQn);
}

void DMA_UART6_TX_IRQHandler(void)
{
	HAL_DMA_IRQHandler(&HdmaHandle_uart6_tx);
}

void DMA_UART6_RX_IRQHandler(void)
{
	HAL_DMA_IRQHandler(&HdmaHandle_uart6_rx);
}
#endif
