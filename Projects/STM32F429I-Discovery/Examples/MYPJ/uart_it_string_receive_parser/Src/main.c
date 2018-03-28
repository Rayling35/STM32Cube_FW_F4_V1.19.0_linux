#include "system_initialization.h"
#include "uart_printf.h"
#include "main.h"
#include "api_define.h"
#include "uart7.h"
#include "uart_callback.h"
#include "uart_callback_string_parser.h"


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
		struct uart_api *uart7 = (struct uart_api *)uart7_binding();
		uart7->transmit_it(buffer7, 10);
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
	
	struct uart_api *uart7 = (struct uart_api *)uart7_binding();
	uart7->init();
	
	uart7->receive_it(&uart_callback_string_byte, 1);
	uart7_rx_callbake_flag = SET;
	
	struct_ble_cmd_data *cmd_data;
	while(1) {
		cmd_data = get_data();
		if(cmd_data != NULL) {
			printf("%s\r\n", cmd_data->start);
		}
	}
}
