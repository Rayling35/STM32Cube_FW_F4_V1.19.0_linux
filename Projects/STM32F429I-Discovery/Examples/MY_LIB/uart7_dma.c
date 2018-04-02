#include "stm32f4xx_hal.h"
#include "uart7_dma.h"
#include "uart7.h"
#include "api_define.h"


#ifdef UART7_DMA
static DMA_HandleTypeDef HdmaHandle_uart7_tx;
static DMA_HandleTypeDef HdmaHandle_uart7_rx;

void _DMA_UART7_MspInit(void)
{
	struct uart_api *uart7 = (struct uart_api *)uart7_binding();
	
	DMA_UART7_CLK_ENABLE();
	
	HdmaHandle_uart7_tx.Instance                 = DMA_UART7_TX_STREAM;
	HdmaHandle_uart7_tx.Init.Channel             = DMA_UART7_TX_CHANNEL;
	HdmaHandle_uart7_tx.Init.Direction           = DMA_MEMORY_TO_PERIPH;
	HdmaHandle_uart7_tx.Init.PeriphInc           = DMA_PINC_DISABLE;
	HdmaHandle_uart7_tx.Init.MemInc              = DMA_MINC_ENABLE;
	HdmaHandle_uart7_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	HdmaHandle_uart7_tx.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;
	HdmaHandle_uart7_tx.Init.Mode                = DMA_CIRCULAR;
	HdmaHandle_uart7_tx.Init.Priority            = DMA_PRIORITY_LOW;
	HdmaHandle_uart7_tx.Init.FIFOMode            = DMA_FIFOMODE_DISABLE;
	HdmaHandle_uart7_tx.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;
	HdmaHandle_uart7_tx.Init.MemBurst            = DMA_MBURST_INC4;
	HdmaHandle_uart7_tx.Init.PeriphBurst         = DMA_PBURST_INC4;
	HAL_DMA_Init(&HdmaHandle_uart7_tx);
	
	__HAL_LINKDMA(uart7->handle, hdmatx, HdmaHandle_uart7_tx);
	
	HdmaHandle_uart7_rx.Instance                 = DMA_UART7_RX_STREAM;
	HdmaHandle_uart7_rx.Init.Channel             = DMA_UART7_RX_CHANNEL;
	HdmaHandle_uart7_rx.Init.Direction           = DMA_PERIPH_TO_MEMORY;
	HdmaHandle_uart7_rx.Init.PeriphInc           = DMA_PINC_DISABLE;
	HdmaHandle_uart7_rx.Init.MemInc              = DMA_MINC_ENABLE;
	HdmaHandle_uart7_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	HdmaHandle_uart7_rx.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;
	HdmaHandle_uart7_rx.Init.Mode                = DMA_NORMAL;
	HdmaHandle_uart7_rx.Init.Priority            = DMA_PRIORITY_LOW;
	HdmaHandle_uart7_rx.Init.FIFOMode            = DMA_FIFOMODE_DISABLE;
	HdmaHandle_uart7_rx.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;
	HdmaHandle_uart7_rx.Init.MemBurst            = DMA_MBURST_INC4;
	HdmaHandle_uart7_rx.Init.PeriphBurst         = DMA_PBURST_INC4;
	HAL_DMA_Init(&HdmaHandle_uart7_rx);
	
	__HAL_LINKDMA(uart7->handle, hdmarx, HdmaHandle_uart7_rx);
	
	HAL_NVIC_SetPriority(DMA_UART7_TX_IRQn, 0, 1);
	HAL_NVIC_EnableIRQ(DMA_UART7_TX_IRQn);
	
	HAL_NVIC_SetPriority(DMA_UART7_RX_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(DMA_UART7_RX_IRQn);
}

void _DMA_UART7_MspDeInit(void)
{
	HAL_DMA_DeInit(&HdmaHandle_uart7_tx);
	HAL_DMA_DeInit(&HdmaHandle_uart7_rx);
	
	HAL_NVIC_DisableIRQ(DMA_UART7_TX_IRQn);
	HAL_NVIC_DisableIRQ(DMA_UART7_RX_IRQn);
}

void DMA_UART7_TX_IRQHandler(void)
{
	HAL_DMA_IRQHandler(&HdmaHandle_uart7_tx);
}

void DMA_UART7_RX_IRQHandler(void)
{
	HAL_DMA_IRQHandler(&HdmaHandle_uart7_rx);
}
#endif
