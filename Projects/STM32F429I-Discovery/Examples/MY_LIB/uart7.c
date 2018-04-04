#include "uart7.h"
#include "api_define.h"


static UART_HandleTypeDef UartHandle7;

void _UART7_MspInit(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;

	UART7_TX_GPIO_CLK_ENABLE();
	UART7_RX_GPIO_CLK_ENABLE();
	UART7_CLK_ENABLE(); 

	GPIO_InitStruct.Pin       = UART7_TX_PIN;
	GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull      = GPIO_NOPULL;
	GPIO_InitStruct.Speed     = GPIO_SPEED_FAST;
	GPIO_InitStruct.Alternate = UART7_TX_AF;
	HAL_GPIO_Init(UART7_TX_GPIO_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.Pin       = UART7_RX_PIN;
	GPIO_InitStruct.Alternate = UART7_RX_AF;
	HAL_GPIO_Init(UART7_RX_GPIO_PORT, &GPIO_InitStruct);

	#ifdef UART7_IT
	HAL_NVIC_SetPriority(UART7_IRQn, 0, 1);
	HAL_NVIC_EnableIRQ(UART7_IRQn);
	#endif
}

void _UART7_MspDeInit(void)
{
	UART7_FORCE_RESET();
	UART7_RELEASE_RESET();

	HAL_GPIO_DeInit(UART7_TX_GPIO_PORT, UART7_TX_PIN);
	HAL_GPIO_DeInit(UART7_RX_GPIO_PORT, UART7_RX_PIN);

	#ifdef UART7_IT
	HAL_NVIC_DisableIRQ(UART7_IRQn);
	#endif
}

void uart7_init(void)
{
	_UART7_MspDeInit();
	_UART7_MspInit();
	UartHandle7.Instance          = UART7;
	UartHandle7.Init.BaudRate     = UART7_BAUDRATE;
	UartHandle7.Init.WordLength   = UART_WORDLENGTH_8B;
	UartHandle7.Init.StopBits     = UART_STOPBITS_1;
	UartHandle7.Init.Parity       = UART_PARITY_NONE;
	UartHandle7.Init.HwFlowCtl    = UART_HWCONTROL_NONE;
	UartHandle7.Init.Mode         = UART_MODE_TX_RX;
	UartHandle7.Init.OverSampling = UART_OVERSAMPLING_16;
	HAL_UART_Init(&UartHandle7);
}

int uart7_transmit(uint8_t *data, uint16_t length, uint32_t timeout)
{
	HAL_UART_Transmit(&UartHandle7, data, length, timeout);
	return 0;
}

int uart7_receive(uint8_t *data, uint16_t length, uint32_t timeout)
{
	HAL_UART_Receive(&UartHandle7, data, length, timeout);
	return 0;
}

#ifdef UART7_IT
int uart7_transmit_it(uint8_t *data, uint16_t length)
{
	HAL_UART_Transmit_IT(&UartHandle7, data, length);
	return 0;
}

int uart7_receive_it(uint8_t *data, uint16_t length)
{
	HAL_UART_Receive_IT(&UartHandle7, data, length);
	return 0;
}
#ifdef UART7_DMA
int uart7_transmit_dma(uint8_t *data, uint16_t length)
{
	HAL_UART_Transmit_DMA(&UartHandle7, data, length);
	return 0;
}

int uart7_receive_dma(uint8_t *data, uint16_t length)
{
	HAL_UART_Receive_DMA(&UartHandle7, data, length);
	return 0;
}
#endif
#endif

struct uart_api uart7_api = {
	.handle = &UartHandle7,
	.init = uart7_init,
	.transmit = uart7_transmit,
	.receive = uart7_receive,
	#ifdef UART7_IT
	.transmit_it = uart7_transmit_it,
	.receive_it = uart7_receive_it,
	#ifdef UART7_DMA
	.transmit_dma = uart7_transmit_dma,
	.receive_dma = uart7_receive_dma,
	#endif
	#endif
};

struct uart_api* uart7_binding(void)
{
	return &uart7_api; //¶Ç»¼¦ì¸m
}

#ifdef UART7_IT
void UART7_IRQHandler(void)
{
	HAL_UART_IRQHandler(&UartHandle7);
}
#endif

#ifdef UART7_DMA
static DMA_HandleTypeDef HdmaHandle_uart7_tx;
static DMA_HandleTypeDef HdmaHandle_uart7_rx;

void _DMA_UART7_MspInit(void)
{
	DMA_UART7_CLK_ENABLE();
	
	HdmaHandle_uart7_tx.Instance                 = DMA_UART7_TX_STREAM;
	HdmaHandle_uart7_tx.Init.Channel             = DMA_UART7_TX_CHANNEL;
	HdmaHandle_uart7_tx.Init.Direction           = DMA_MEMORY_TO_PERIPH;
	HdmaHandle_uart7_tx.Init.PeriphInc           = DMA_PINC_DISABLE;
	HdmaHandle_uart7_tx.Init.MemInc              = DMA_MINC_ENABLE;
	HdmaHandle_uart7_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	HdmaHandle_uart7_tx.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;
	HdmaHandle_uart7_tx.Init.Mode                = DMA_NORMAL;
	HdmaHandle_uart7_tx.Init.Priority            = DMA_PRIORITY_LOW;
	HdmaHandle_uart7_tx.Init.FIFOMode            = DMA_FIFOMODE_DISABLE;
	HdmaHandle_uart7_tx.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;
	HdmaHandle_uart7_tx.Init.MemBurst            = DMA_MBURST_INC4;
	HdmaHandle_uart7_tx.Init.PeriphBurst         = DMA_PBURST_INC4;
	HAL_DMA_Init(&HdmaHandle_uart7_tx);
	
	__HAL_LINKDMA(&UartHandle7, hdmatx, HdmaHandle_uart7_tx);
	
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
	
	__HAL_LINKDMA(&UartHandle7, hdmarx, HdmaHandle_uart7_rx);
	
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
