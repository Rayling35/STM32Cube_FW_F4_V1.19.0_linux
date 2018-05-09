#include "system_initialization.h"
#include "uart_printf.h"
#include "main.h"
#include "api_define.h"
#include "uart3.h"
#include "uart6.h"
#include "uart7.h"


uint8_t myBuffer[] = "\nGPIO_INT\r\n";
uint8_t Buffer[1];
uint8_t ok[] = "ok";

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
		printf("\n%s\r\n", myBuffer);
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
	struct uart_api *uart3 = (struct uart_api *)uart3_binding();
	struct uart_api *uart6 = (struct uart_api *)uart6_binding();
	struct uart_api *uart7 = (struct uart_api *)uart7_binding();
	uart3->init();
	uart6->init();
	uart7->init();
  EXTILine0_Config();
	
  while(1) {
		uart3->receive(Buffer, 1, 1000);
		uart6->receive(Buffer, 1, 1000);
		uart7->receive(Buffer, 1, 1000);
		if(Buffer[0] == 0x66) {
			printf("Hi fff\r\n");
			uart3->transmit(ok, 2, 1000);
			uart6->transmit(ok, 2, 1000);
			uart7->transmit(ok, 2, 1000);
		}		
  }
}
