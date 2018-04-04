#include "uart6.h"
#include "api_define.h"


static UART_HandleTypeDef UartHandle6;

void _UART6_MspInit(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;

	USART6_TX_GPIO_CLK_ENABLE();
	USART6_RX_GPIO_CLK_ENABLE();
	USART6_CLK_ENABLE(); 

	GPIO_InitStruct.Pin       = USART6_TX_PIN;
	GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull      = GPIO_NOPULL;
	GPIO_InitStruct.Speed     = GPIO_SPEED_FAST;
	GPIO_InitStruct.Alternate = USART6_TX_AF;
	HAL_GPIO_Init(USART6_TX_GPIO_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.Pin       = USART6_RX_PIN;
	GPIO_InitStruct.Alternate = USART6_RX_AF;
	HAL_GPIO_Init(USART6_RX_GPIO_PORT, &GPIO_InitStruct);

	#ifdef UART6_IT
	HAL_NVIC_SetPriority(USART6_IRQn, 0, 1);
	HAL_NVIC_EnableIRQ(USART6_IRQn);
	#endif
}

void _UART6_MspDeInit(void)
{
	USART6_FORCE_RESET();
	USART6_RELEASE_RESET();

	HAL_GPIO_DeInit(USART6_TX_GPIO_PORT, USART6_TX_PIN);
	HAL_GPIO_DeInit(USART6_RX_GPIO_PORT, USART6_RX_PIN);

	#ifdef UART6_IT
	HAL_NVIC_DisableIRQ(USART6_IRQn);
	#endif
}

void uart6_init(void)
{
	_UART6_MspDeInit();
	_UART6_MspInit();
	UartHandle6.Instance          = USART6;
	UartHandle6.Init.BaudRate     = USART6_BAUDRATE;
	UartHandle6.Init.WordLength   = UART_WORDLENGTH_8B;
	UartHandle6.Init.StopBits     = UART_STOPBITS_1;
	UartHandle6.Init.Parity       = UART_PARITY_NONE;
	UartHandle6.Init.HwFlowCtl    = UART_HWCONTROL_NONE;
	UartHandle6.Init.Mode         = UART_MODE_TX_RX;
	UartHandle6.Init.OverSampling = UART_OVERSAMPLING_16;
	HAL_UART_Init(&UartHandle6);
}

int uart6_transmit(uint8_t *data, uint16_t length, uint32_t timeout)
{
	HAL_UART_Transmit(&UartHandle6, data, length, timeout);
	return 0;
}

int uart6_receive(uint8_t *data, uint16_t length, uint32_t timeout)
{
	HAL_UART_Receive(&UartHandle6, data, length, timeout);
	return 0;
}

#ifdef UART6_IT
int uart6_transmit_it(uint8_t *data, uint16_t length)
{
	HAL_UART_Transmit_IT(&UartHandle6, data, length);
	return 0;
}

int uart6_receive_it(uint8_t *data, uint16_t length)
{
	HAL_UART_Receive_IT(&UartHandle6, data, length);
	return 0;
}
#ifdef UART6_DMA
int uart6_transmit_dma(uint8_t *data, uint16_t length)
{
	HAL_UART_Transmit_DMA(&UartHandle6, data, length);
	return 0;
}

int uart6_receive_dma(uint8_t *data, uint16_t length)
{
	HAL_UART_Receive_DMA(&UartHandle6, data, length);
	return 0;
}
#endif
#endif

struct uart_api uart6_api = {
	.handle = &UartHandle6,
	.init = uart6_init,
	.transmit = uart6_transmit,
	.receive = uart6_receive,
	#ifdef UART6_IT
	.transmit_it = uart6_transmit_it,
	.receive_it = uart6_receive_it,
	#ifdef UART6_DMA
	.transmit_dma = uart6_transmit_dma,
	.receive_dma = uart6_receive_dma,
	#endif
	#endif
};

struct uart_api* uart6_binding(void)
{
	return &uart6_api; //¶Ç»¼¦ì¸m
}

#ifdef UART6_IT
void USART6_IRQHandler(void)
{
	HAL_UART_IRQHandler(&UartHandle6);
}
#endif

#ifdef UART6_DMA
static DMA_HandleTypeDef HdmaHandle_uart6_tx;
static DMA_HandleTypeDef HdmaHandle_uart6_rx;

void _DMA_UART6_MspInit(void)
{
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
	
	__HAL_LINKDMA(&UartHandle6, hdmatx, HdmaHandle_uart6_tx);
	
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
	
	__HAL_LINKDMA(&UartHandle6, hdmarx, HdmaHandle_uart6_rx);
	
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
