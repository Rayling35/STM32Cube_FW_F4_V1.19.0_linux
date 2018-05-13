#include "uart_common_api.h"
#include "uart_driver.h"

struct uart_data {
	uint32_t temp;
};

struct uart_config {
	UART_HandleTypeDef *UartHandle;
	uint32_t BaudRate;
	uint32_t WordLength;
	uint32_t StopBits;
	uint32_t Parity;
	uint32_t HwFlowCtl;
	uint32_t Mode;
	uint32_t OverSampling;
};

/*-----------API--------------*/
static int receive_data(struct device *dev, uint8_t *rxBuffer, uint16_t length, uint16_t timeout)
{
	const struct uart_config *config = dev->config;
	UART_HandleTypeDef *UartHandle = config->UartHandle;
	
	return HAL_UART_Receive(UartHandle, rxBuffer, length, timeout);
}

static int transmit_data(struct device *dev, uint8_t *txBuffer, uint16_t length, uint16_t timeout)
{
	const struct uart_config *config = dev->config;
	UART_HandleTypeDef *UartHandle = config->UartHandle;

	return HAL_UART_Transmit(UartHandle, txBuffer, length, timeout);
}

static const struct uart_common_api uart3_driver_api = {
	.read = receive_data,
	.write = transmit_data,
};


#ifdef UART3
static struct uart_data uart3_data;

static UART_HandleTypeDef UartHandle3;

static const struct uart_config uart3_config = {
	.UartHandle   = &UartHandle3,
	.BaudRate     = 115200,
	.WordLength   = UART_WORDLENGTH_8B,
	.StopBits     = UART_STOPBITS_1,
	.Parity       = UART_PARITY_NONE,
	.HwFlowCtl    = UART_HWCONTROL_NONE,
	.Mode         = UART_MODE_TX_RX,
	.OverSampling = UART_OVERSAMPLING_16,
};

void _UART3_MspInit(void)
{  
  GPIO_InitTypeDef  GPIO_InitStruct;
  
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_USART3_CLK_ENABLE(); 
  
  GPIO_InitStruct.Pin       = GPIO_PIN_8;
  GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull      = GPIO_NOPULL;
  GPIO_InitStruct.Speed     = GPIO_SPEED_FAST;
  GPIO_InitStruct.Alternate = GPIO_AF7_USART3;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
    
  GPIO_InitStruct.Pin       = GPIO_PIN_9;
  GPIO_InitStruct.Alternate = GPIO_AF7_USART3;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
#ifdef UART3_IT
  HAL_NVIC_SetPriority(USART3_IRQn, 0, 1);
  HAL_NVIC_EnableIRQ(USART3_IRQn);
#endif
}

void _UART3_MspDeInit(void)
{
  __HAL_RCC_USART3_FORCE_RESET();
  __HAL_RCC_USART3_RELEASE_RESET();

  HAL_GPIO_DeInit(GPIOD, GPIO_PIN_8);
  HAL_GPIO_DeInit(GPIOD, GPIO_PIN_9);
#ifdef UART3_IT
  HAL_NVIC_DisableIRQ(USART3_IRQn);
#endif
}

static int uart3_init(struct device *dev)
{
	const struct uart_config *config = dev->config;
	UART_HandleTypeDef *UartHandle = config->UartHandle;
	
	_UART3_MspDeInit();
	_UART3_MspInit();
	UartHandle->Instance          = USART3;
	UartHandle->Init.BaudRate     = config->BaudRate;
	UartHandle->Init.WordLength   = config->WordLength;
	UartHandle->Init.StopBits     = config->StopBits;
	UartHandle->Init.Parity       = config->Parity;
	UartHandle->Init.HwFlowCtl    = config->HwFlowCtl;
	UartHandle->Init.Mode         = config->Mode;
	UartHandle->Init.OverSampling = config->OverSampling;
	HAL_UART_Init(UartHandle);
	
	return 0;
}

struct device uart_3 = {
	.api    = &uart3_driver_api,
	.data   = &uart3_data,
	.config = &uart3_config,
	.init   = uart3_init,
};

#ifdef UART3_IT
void USART3_IRQHandler(void)
{
  HAL_UART_IRQHandler(&UartHandle3);
}
#endif

uint32_t uart3_binding(void)
{
	return (uint32_t)&uart_3;
}
#endif
