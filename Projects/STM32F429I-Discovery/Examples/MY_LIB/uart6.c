#include "uart6.h"

UART_HandleTypeDef UartHandle6;

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


#ifdef UART6_IT
void USART6_IRQHandler(void)
{
  HAL_UART_IRQHandler(&UartHandle6);
}
#endif


void uart6_init(void)
{
	_UART6_MspDeInit();
	_UART6_MspInit();
  UartHandle6.Instance          = USART6;
  UartHandle6.Init.BaudRate     = 115200;
  UartHandle6.Init.WordLength   = UART_WORDLENGTH_8B;
  UartHandle6.Init.StopBits     = UART_STOPBITS_1;
  UartHandle6.Init.Parity       = UART_PARITY_NONE;
  UartHandle6.Init.HwFlowCtl    = UART_HWCONTROL_NONE;
  UartHandle6.Init.Mode         = UART_MODE_TX_RX;
  UartHandle6.Init.OverSampling = UART_OVERSAMPLING_16;
  HAL_UART_Init(&UartHandle6);
}
