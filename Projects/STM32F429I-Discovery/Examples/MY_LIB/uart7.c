#include "uart7.h"
#include "api_define.h"


#ifdef UART7_ENABLE
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
	UartHandle7.Init.BaudRate     = 115200;
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

struct uart_api uart7_api = {
	.handle = &UartHandle7,
	.init = uart7_init,
	.transmit = uart7_transmit,
	.receive = uart7_receive,
	.transmit_it = uart7_transmit_it,
	.receive_it = uart7_receive_it,
};

uint32_t uart7_binding(void)
{
	return (uint32_t)&uart7_api; //¶Ç»¼¦ì¸m 4Byte
}

#ifdef UART7_IT
void UART7_IRQHandler(void)
{
	HAL_UART_IRQHandler(&UartHandle7);
}
#endif
#endif //#ifdef UART7_ENABLE
