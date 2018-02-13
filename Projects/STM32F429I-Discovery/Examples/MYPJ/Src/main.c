#include "main.h"

extern UART_HandleTypeDef UartHandle3;

uint8_t aTxBuffer[] = "Hello_TX";
uint8_t aRxBuffer[10];

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
//		printf("\nGPIO_INT Button Trigger!\r\n");
		HAL_UART_Transmit_IT(&UartHandle3, (uint8_t *)aTxBuffer, 10);
  }
}


int main(void)
{
	system_initialization();
	uart_printf_init();
	uart3_init();
	
  EXTILine0_Config();
	
	HAL_UART_Receive_IT(&UartHandle3, (uint8_t *)aRxBuffer, 10);
//	printf("1\r\n");
	
  while(1) {
  }
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *UartHandle3)
{
	printf("This TX Callback\r\n");
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle3)
{
	printf("RX Response %c\r\n", aRxBuffer[1]);
}
