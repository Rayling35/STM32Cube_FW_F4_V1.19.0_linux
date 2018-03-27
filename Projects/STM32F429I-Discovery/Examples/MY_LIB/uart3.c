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
	UartHandle3.Init.BaudRate     = 115200;
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

struct uart_api uart3_api = {
	.handle = &UartHandle3,
	.init = uart3_init,
	.transmit = uart3_transmit,
	.receive = uart3_receive,
	#ifdef UART3_IT
	.transmit_it = uart3_transmit_it,
	.receive_it = uart3_receive_it,
	.transmit_dma = uart3_transmit_dma,
	.receive_dma = uart3_receive_dma,
	#endif
};

uint32_t uart3_binding(void)
{
	return (uint32_t)&uart3_api; //¶Ç»¼¦ì¸m 4Byte
}

#ifdef UART3_IT
void USART3_IRQHandler(void)
{
	HAL_UART_IRQHandler(&UartHandle3);
}
#endif
