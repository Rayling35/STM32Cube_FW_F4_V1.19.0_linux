#include "system_initialization.h"
#include "uart_printf.h"
#include "main.h"
#include "api_define.h"
#include "uart3.h"
#include "uart6.h"
#include "uart7.h"
#include "uart_callback.h"
#include "uart_it_callback_parser.h"


uint8_t buffer3[10] = "Hi buf 3\r\n";
uint8_t buffer6[10] = "Hi buf 6\r\n";
uint8_t buffer7[10] = "Hi buf 7\r\n";

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
	#ifdef UART3_IT
		struct uart_api *uart3 = (struct uart_api *)uart3_binding();
		uart3->transmit_it(buffer3, 10);
	#elif UART6_IT
		struct uart_api *uart6 = (struct uart_api *)uart6_binding();
		uart6->transmit_it(buffer6, 10);
	#elif UART7_IT
		struct uart_api *uart7 = (struct uart_api *)uart7_binding();
		uart7->transmit_it(buffer7, 10);
	#endif
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
	EXTILine0_Config();
	
#ifdef UART3_IT
	struct uart_api *uart3 = (struct uart_api *)uart3_binding();
	uart3->init();
	uart3->receive_it(&uart_it_callback_string_byte, 1);
	uart3_rx_callbake_flag = SET;
#elif UART6_IT
	struct uart_api *uart6 = (struct uart_api *)uart6_binding();
	uart6->init();
	uart6->receive_it(&uart_it_callback_string_byte, 1);
	uart6_rx_callbake_flag = SET;
#elif UART7_IT
	struct uart_api *uart7 = (struct uart_api *)uart7_binding();
	uart7->init();
	uart7->receive_it(&uart_it_callback_string_byte, 1);
	uart7_rx_callbake_flag = SET;
#endif
	
	uint8_t *string_checkout;
	
	while(1) {
		string_checkout = uart_it_callback_string_out();
		if(string_checkout != NULL) {
			printf("%s\r\n", string_checkout);
		}
	}
}
