#include "system_initialization.h"
#include "uart_printf.h"
#include "main.h"
#include "api_define.h"
#include "uart3.h"
#include "uart6.h"
#include "uart7.h"


uint8_t TxBuffer[] = "GPIO_INT\r\n";
uint8_t RxData3;
uint8_t RxData6;
uint8_t RxData7;

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
	struct uart_api *uart3 = (struct uart_api *)uart3_binding();
	struct uart_api *uart6 = (struct uart_api *)uart6_binding();
	struct uart_api *uart7 = (struct uart_api *)uart7_binding();
  if(GPIO_Pin == GPIO_PIN_0) {
		uart3->transmit_it((uint8_t *)TxBuffer, 10);
		uart6->transmit_it((uint8_t *)TxBuffer, 10);
		uart7->transmit_it((uint8_t *)TxBuffer, 10);
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
	
	uart3->receive_it(&RxData3, 1);
	uart6->receive_it(&RxData6, 1);
	uart7->receive_it(&RxData7, 1);
}


void HAL_UART_TxCpltCallback(UART_HandleTypeDef *UartHandle)
{
	struct uart_api *uart3 = (struct uart_api *)uart3_binding();
	struct uart_api *uart6 = (struct uart_api *)uart6_binding();
	struct uart_api *uart7 = (struct uart_api *)uart7_binding();
	
	if(UartHandle == uart3->handle) {
		printf("TX callback UART3\r\n");
	}
	if(UartHandle == uart6->handle) {
		printf("TX callback UART6\r\n");
	}
	if(UartHandle == uart7->handle) {
		printf("TX callback UART7\r\n");
	}
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle)
{
	struct uart_api *uart3 = (struct uart_api *)uart3_binding();
	struct uart_api *uart6 = (struct uart_api *)uart6_binding();
	struct uart_api *uart7 = (struct uart_api *)uart7_binding();
	
	if(UartHandle == uart3->handle) {
		printf("RX callback UART3:%c\r\n", RxData3);
		uart3->receive_it(&RxData3, 1);
	}
	if(UartHandle == uart6->handle) {
		printf("RX callback UART6:%c\r\n", RxData6);
		uart6->receive_it(&RxData6, 1);
	}
	if(UartHandle == uart7->handle) {
		printf("RX callback UART7:%c\r\n", RxData7);
		uart7->receive_it(&RxData7, 1);
	}
}

 void HAL_UART_ErrorCallback(UART_HandleTypeDef *UartHandle)
{
	struct uart_api *uart3 = (struct uart_api *)uart3_binding();
	struct uart_api *uart6 = (struct uart_api *)uart6_binding();
	struct uart_api *uart7 = (struct uart_api *)uart7_binding();
	
	if(UartHandle == uart3->handle) {
		printf("Error Callback UART3\r\n");
	}
	if(UartHandle == uart6->handle) {
		printf("Error Callback UART6\r\n");
	}
	if(UartHandle == uart7->handle) {
		printf("Error Callback UART7\r\n");
	}	
}
