#include "system_initialization.h"
#include "uart_printf.h"
#include "device.h"
#include "uart_driver.h"
#include "uart_common_api.h"
#include "main.h"


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
	
	struct device *uart3 = uart3_device_binding();
	struct device *uart6 = uart6_device_binding();
	struct device *uart7 = uart7_device_binding();
	uart_init(uart3);
	uart_init(uart6);
	uart_init(uart7);
	printf("UART device init\r\n");
	
	EXTILine0_Config();
	
	while(1) {
		uart_receive(uart3, Buffer, 1);
		uart_receive(uart6, Buffer, 1);
		uart_receive(uart7, Buffer, 1);
		if(Buffer[0] == 0x66) {
			printf("Hi fff\r\n");
			uart_transmit(uart3, ok, 2);
			uart_transmit(uart6, ok, 2);
			uart_transmit(uart7, ok, 2);
		}
  }
}
