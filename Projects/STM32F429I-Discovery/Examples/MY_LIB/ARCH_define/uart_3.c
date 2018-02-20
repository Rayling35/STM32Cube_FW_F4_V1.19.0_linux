#include <uart_api.h>
#include "uart_3.h"

struct uart3_data {
	uint32_t temp;
};

struct uart3_config {
	uint32_t BaudRate;
	uint32_t WordLength;
  uint32_t StopBits;
  uint32_t Parity;
  uint32_t HwFlowCtl;
  uint32_t Mode;
  uint32_t OverSampling;
};

static UART_HandleTypeDef UartHandle3;

               /*-----------API--------------*/
static int receive_data(struct device *dev, uint8_t *rxBuffer)
{
	HAL_UART_Receive(&UartHandle3, rxBuffer, 1, 5000);
	return 0;
}

static int transmit_data(struct device *dev, uint8_t *txBuffer)
{
	HAL_UART_Transmit(&UartHandle3, txBuffer, 8, 5000);
	return 0;
}
               /*-----------Define-----------*/
static const struct uart_api uart3_api = {
	.read = receive_data,
	.write = transmit_data,
};

static struct uart3_data uart3_data;

static const struct uart3_config uart3_config = {
	.BaudRate     = 115200,
	.WordLength   = UART_WORDLENGTH_8B,
  .StopBits     = UART_STOPBITS_1,
  .Parity       = UART_PARITY_NONE,
  .HwFlowCtl    = UART_HWCONTROL_NONE,
  .Mode         = UART_MODE_TX_RX,
  .OverSampling = UART_OVERSAMPLING_16,
};

static int uart3_init(struct device *dev)
{
	const struct uart3_config *config = dev->config;
	
	UartHandle3.Instance          = USART3;
	UartHandle3.Init.BaudRate     = config->BaudRate;
	UartHandle3.Init.WordLength   = config->WordLength;
	UartHandle3.Init.StopBits     = config->StopBits;
	UartHandle3.Init.Parity       = config->Parity;
	UartHandle3.Init.HwFlowCtl    = config->HwFlowCtl;
	UartHandle3.Init.Mode         = config->Mode;
	UartHandle3.Init.OverSampling = config->OverSampling;
	HAL_UART_Init(&UartHandle3);
	
	return 0;
}

struct device uart_3 = {
	.api     = &uart3_api,
	.data   = &uart3_data,
	.config = &uart3_config,
	.init     = uart3_init,
};


/*----------External----------*/
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

#ifdef UART3_IT
void USART3_IRQHandler(void)
{
  HAL_UART_IRQHandler(&UartHandle3);
}
#endif
