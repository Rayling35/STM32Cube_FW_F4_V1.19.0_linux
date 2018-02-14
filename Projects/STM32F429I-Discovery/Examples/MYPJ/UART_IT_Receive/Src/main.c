#include "main.h"

extern UART_HandleTypeDef UartHandle3;

uint8_t TxBuffer[] = "\nGPIO_INT\r\n";
uint8_t RxBuffer[50];

static void EXTILine0_Config(void)
{
  GPIO_InitTypeDef   GPIO_InitStructure;

  /* Enable GPIOA clock */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  
  /* Configure PA0 pin as input floating */
  GPIO_InitStructure.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStructure.Pull = GPIO_NOPULL;
  GPIO_InitStructure.Pin = GPIO_PIN_0;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* Enable and set EXTI Line0 Interrupt to the lowest priority */
  HAL_NVIC_SetPriority(EXTI0_IRQn, 2, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if(GPIO_Pin == GPIO_PIN_0) {
		HAL_UART_Transmit_IT(&UartHandle3, (uint8_t *)TxBuffer, 15);
  }
}

void EXTI0_IRQHandler(void)
{
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
}

int main(void)
{
	system_initialization();
	uart_printf_init();
	uart3_init();
  EXTILine0_Config();
	
  while(1) {
		HAL_UART_Receive_IT(&UartHandle3, RxBuffer, 50);
  }
}


void HAL_UART_TxCpltCallback(UART_HandleTypeDef *UartHandle3)
{
	printf("TX callback:~\r\n");
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle3)
{
	printf("\nRX callback:%s\r\n", RxBuffer);
}
