#include "uart3.h"
#include "api_define.h"


static UART_HandleTypeDef UartHandle3;

void _UART3_MspInit(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;

	USART3_TX_GPIO_CLK_ENABLE();
	USART3_RX_GPIO_CLK_ENABLE();
	USART3_CLK_ENABLE(); 

	GPIO_InitStruct.Pin       = USART3_TX_PIN;
	GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull      = GPIO_NOPULL;
	GPIO_InitStruct.Speed     = GPIO_SPEED_FAST;
	GPIO_InitStruct.Alternate = USART3_TX_AF;
	HAL_GPIO_Init(USART3_TX_GPIO_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.Pin       = USART3_RX_PIN;
	GPIO_InitStruct.Alternate = USART3_RX_AF;
	HAL_GPIO_Init(USART3_RX_GPIO_PORT, &GPIO_InitStruct);

	#ifdef UART3_IT
	HAL_NVIC_SetPriority(USART3_IRQn, 0, 1);
	HAL_NVIC_EnableIRQ(USART3_IRQn);
	#endif
}

void _UART3_MspDeInit(void)
{
	USART3_FORCE_RESET();
	USART3_RELEASE_RESET();

	HAL_GPIO_DeInit(USART3_TX_GPIO_PORT, USART3_TX_PIN);
	HAL_GPIO_DeInit(USART3_RX_GPIO_PORT, USART3_RX_PIN);

	#ifdef UART3_IT
	HAL_NVIC_DisableIRQ(USART3_IRQn);
	#endif
}

void uart3_init(void)
{
	_UART3_MspDeInit();
	_UART3_MspInit();
	UartHandle3.Instance          = USART3;
	UartHandle3.Init.BaudRate     = USART3_BAUDRATE;
	UartHandle3.Init.WordLength   = UART_WORDLENGTH_8B;
	UartHandle3.Init.StopBits     = UART_STOPBITS_1;
	UartHandle3.Init.Parity       = UART_PARITY_NONE;
	UartHandle3.Init.HwFlowCtl    = UART_HWCONTROL_NONE;
	UartHandle3.Init.Mode         = UART_MODE_TX_RX;
	UartHandle3.Init.OverSampling = UART_OVERSAMPLING_16;
	HAL_UART_Init(&UartHandle3);
}

int uart3_transmit(uint8_t *data, uint16_t length, uint32_t timeout)
{
	HAL_UART_Transmit(&UartHandle3, data, length, timeout);
	return 0;
}

int uart3_receive(uint8_t *data, uint16_t length, uint32_t timeout)
{
	HAL_UART_Receive(&UartHandle3, data, length, timeout);
	return 0;
}

#ifdef UART3_IT
int uart3_transmit_it(uint8_t *data, uint16_t length)
{
	HAL_UART_Transmit_IT(&UartHandle3, data, length);
	return 0;
}

int uart3_receive_it(uint8_t *data, uint16_t length)
{
	HAL_UART_Receive_IT(&UartHandle3, data, length);
	return 0;
}
#ifdef UART3_DMA
int uart3_transmit_dma(uint8_t *data, uint16_t length)
{
	HAL_UART_Transmit_DMA(&UartHandle3, data, length);
	return 0;
}

int uart3_receive_dma(uint8_t *data, uint16_t length)
{
	HAL_UART_Receive_DMA(&UartHandle3, data, length);
	return 0;
}
#endif
#endif

struct uart_api uart3_api = {
	.handle = &UartHandle3,
	.init = uart3_init,
	.transmit = uart3_transmit,
	.receive = uart3_receive,
	#ifdef UART3_IT
	.transmit_it = uart3_transmit_it,
	.receive_it = uart3_receive_it,
	#ifdef UART3_DMA
	.transmit_dma = uart3_transmit_dma,
	.receive_dma = uart3_receive_dma,
	#endif
	#endif
};

struct uart_api* uart3_binding(void)
{
	return &uart3_api; //¶Ç»¼¦ì¸m
}

#ifdef UART3_IT
void USART3_IRQHandler(void)
{
	HAL_UART_IRQHandler(&UartHandle3);
}
#endif

#ifdef UART3_DMA
static DMA_HandleTypeDef HdmaHandle_uart3_tx;
static DMA_HandleTypeDef HdmaHandle_uart3_rx;

void _DMA_UART3_MspInit(void)
{
	DMA_UART3_CLK_ENABLE();
	
	HdmaHandle_uart3_tx.Instance                 = DMA_UART3_TX_STREAM;
	HdmaHandle_uart3_tx.Init.Channel             = DMA_UART3_TX_CHANNEL;
	HdmaHandle_uart3_tx.Init.Direction           = DMA_MEMORY_TO_PERIPH;
	HdmaHandle_uart3_tx.Init.PeriphInc           = DMA_PINC_DISABLE;
	HdmaHandle_uart3_tx.Init.MemInc              = DMA_MINC_ENABLE;
	HdmaHandle_uart3_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	HdmaHandle_uart3_tx.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;
	HdmaHandle_uart3_tx.Init.Mode                = DMA_NORMAL;
	HdmaHandle_uart3_tx.Init.Priority            = DMA_PRIORITY_LOW;
	HdmaHandle_uart3_tx.Init.FIFOMode            = DMA_FIFOMODE_DISABLE;
	HdmaHandle_uart3_tx.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;
	HdmaHandle_uart3_tx.Init.MemBurst            = DMA_MBURST_INC4;
	HdmaHandle_uart3_tx.Init.PeriphBurst         = DMA_PBURST_INC4;
	HAL_DMA_Init(&HdmaHandle_uart3_tx);
	
	__HAL_LINKDMA(&UartHandle3, hdmatx, HdmaHandle_uart3_tx);
	
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
	
	__HAL_LINKDMA(&UartHandle3, hdmarx, HdmaHandle_uart3_rx);
	
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
