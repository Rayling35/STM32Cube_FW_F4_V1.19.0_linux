/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include "system_initialization.h"
#include "uart_printf.h"
#include "stm32f4xx_hal.h"
#include "api_define.h"
#include "uart3.h"
#include "uart6.h"
#include "uart7.h"
#include "uart_callback.h"
#include "main.h"


uint8_t buffer3[10];
uint8_t buffer6[10];
uint8_t buffer7[10];

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
		#ifdef UART3_DMA
		struct uart_api *uart3 = (struct uart_api *)uart3_binding();
		uart3->transmit_dma(buffer3, 10);
		#endif
		
		#ifdef UART6_DMA
		struct uart_api *uart6 = (struct uart_api *)uart6_binding();
		uart6->transmit_dma(buffer6, 10);
		#endif
		
		#ifdef UART7_DMA
		struct uart_api *uart7 = (struct uart_api *)uart7_binding();
		uart7->transmit_dma(buffer7, 10);
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
	
	#ifdef UART3_DMA
	uint8_t RxData3;
	struct uart_api *uart3 = (struct uart_api *)uart3_binding();
	uart3->init();
	uart3->receive_dma(&RxData3, 1);
	uart3_rx_callbake_flag = SET;
	uint16_t u3 = 0;
	#endif
	
	#ifdef UART6_DMA
	uint8_t RxData6;
	struct uart_api *uart6 = (struct uart_api *)uart6_binding();
	uart6->init();
	uart6->receive_dma(&RxData6, 1);
	uart6_rx_callbake_flag = SET;
	uint16_t u6 = 0;
	#endif
	
	#ifdef UART7_DMA
	uint8_t RxData7;
	struct uart_api *uart7 = (struct uart_api *)uart7_binding();
	uart7->init();
	uart7->receive_dma(&RxData7, 1);
	uart7_rx_callbake_flag = SET;
	uint16_t u7 = 0;
	#endif
	
	
	while(1) {
		#ifdef UART3_DMA
		if(uart3_rx_callbake_flag == RESET) {
			buffer3[u3] = RxData3;
			u3++;
			if(u3 >= 10) {
				u3 = 0;
			}
			uart3->receive_dma(&RxData3, 1);
			uart3_rx_callbake_flag = SET;
		}
		#endif
		
		#ifdef UART6_DMA
		if(uart6_rx_callbake_flag == RESET) {
			buffer6[u6] = RxData6;
			u6++;
			if(u6 >= 10) {
				u6 = 0;
			}
			uart6->receive_dma(&RxData6, 1);
			uart6_rx_callbake_flag = SET;
		}
		#endif
		
		#ifdef UART7_DMA
		if(uart7_rx_callbake_flag == RESET) {
			buffer7[u7] = RxData7;
			u7++;
			if(u7 >= 10) {
				u7 = 0;
			}
			uart7->receive_dma(&RxData7, 1);
			uart7_rx_callbake_flag = SET;
		}
		#endif
	}
}
