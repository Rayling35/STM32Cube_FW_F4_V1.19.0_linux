#include "stm32f4xx_hal.h"
#include "uart3_dma.h"
#include "uart3.h"
#include "api_define.h"


#ifdef UART3_DMA
static DMA_HandleTypeDef HdmaHandle_uart3_tx;
static DMA_HandleTypeDef HdmaHandle_uart3_rx;

void _DMA_UART3_MspInit(void)
{
	struct uart_api *uart3 = (struct uart_api *)uart3_binding();
	
	DMA_UART3_CLK_ENABLE();
	
	HdmaHandle_uart3_tx.Instance                 = DMA_UART3_TX_STREAM;
	HdmaHandle_uart3_tx.Init.Channel             = DMA_UART3_TX_CHANNEL;
	HdmaHandle_uart3_tx.Init.Direction           = DMA_MEMORY_TO_PERIPH;
	HdmaHandle_uart3_tx.Init.PeriphInc           = DMA_PINC_DISABLE;
	HdmaHandle_uart3_tx.Init.MemInc              = DMA_MINC_ENABLE;
	HdmaHandle_uart3_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	HdmaHandle_uart3_tx.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;
	HdmaHandle_uart3_tx.Init.Mode                = DMA_CIRCULAR;
	HdmaHandle_uart3_tx.Init.Priority            = DMA_PRIORITY_LOW;
	HdmaHandle_uart3_tx.Init.FIFOMode            = DMA_FIFOMODE_DISABLE;
	HdmaHandle_uart3_tx.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;
	HdmaHandle_uart3_tx.Init.MemBurst            = DMA_MBURST_INC4;
	HdmaHandle_uart3_tx.Init.PeriphBurst         = DMA_PBURST_INC4;
	HAL_DMA_Init(&HdmaHandle_uart3_tx);
	
	__HAL_LINKDMA(uart3->handle, hdmatx, HdmaHandle_uart3_tx);
	
	HdmaHandle_uart3_rx.Instance                 = DMA_UART3_RX_STREAM;
	HdmaHandle_uart3_rx.Init.Channel             = DMA_UART3_RX_CHANNEL;
	HdmaHandle_uart3_rx.Init.Direction           = DMA_PERIPH_TO_MEMORY;
	HdmaHandle_uart3_rx.Init.PeriphInc           = DMA_PINC_DISABLE;
	HdmaHandle_uart3_rx.Init.MemInc              = DMA_MINC_ENABLE;
	HdmaHandle_uart3_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	HdmaHandle_uart3_rx.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;
	HdmaHandle_uart3_rx.Init.Mode                = DMA_NORMAL;
	HdmaHandle_uart3_rx.Init.Priority            = DMA_PRIORITY_LOW;
	HdmaHandle_uart3_rx.Init.FIFOMode            = DMA_FIFOMODE_DISABLE;
	HdmaHandle_uart3_rx.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;
	HdmaHandle_uart3_rx.Init.MemBurst            = DMA_MBURST_INC4;
	HdmaHandle_uart3_rx.Init.PeriphBurst         = DMA_PBURST_INC4;
	HAL_DMA_Init(&HdmaHandle_uart3_rx);
	
	__HAL_LINKDMA(uart3->handle, hdmarx, HdmaHandle_uart3_rx);
	
	HAL_NVIC_SetPriority(DMA_UART3_TX_IRQn, 0, 1);
	HAL_NVIC_EnableIRQ(DMA_UART3_TX_IRQn);
	
	HAL_NVIC_SetPriority(DMA_UART3_RX_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(DMA_UART3_RX_IRQn);
}

void _DMA_UART3_MspDeInit(void)
{
	HAL_DMA_DeInit(&HdmaHandle_uart3_tx);
	HAL_DMA_DeInit(&HdmaHandle_uart3_rx);
	
	HAL_NVIC_DisableIRQ(DMA_UART3_TX_IRQn);
	HAL_NVIC_DisableIRQ(DMA_UART3_RX_IRQn);
}

void DMA_UART3_TX_IRQHandler(void)
{
	HAL_DMA_IRQHandler(&HdmaHandle_uart3_tx);
}

void DMA_UART3_RX_IRQHandler(void)
{
	HAL_DMA_IRQHandler(&HdmaHandle_uart3_rx);
}
#endif
