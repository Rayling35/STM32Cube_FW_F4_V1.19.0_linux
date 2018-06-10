/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include "system_initialization.h"
#include "uart_printf.h"
#include "stm32f4xx_hal.h"
#include "device.h"
#include "uart_driver.h"
#include "uart_common_api.h"
#include "main.h"


uint8_t u3_rx[1];
uint8_t u6_rx[1];
uint8_t u7_rx[1];
uint8_t u3[] = "u3";
uint8_t u6[] = "u6";
uint8_t u7[] = "u7";

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
	
	uart_receive(uart3, u3_rx, 1);
	
	while(1) {
		uart_receive(uart6, u6_rx, 1);
		if(u6_rx[0] == 0x66) {
			printf("Hi u6fff\r\n");
			uart_transmit(uart6, u6, 2);
		}
		
		uart_receive(uart7, u7_rx, 1);
		if(u7_rx[0] == 0x66) {
			printf("Hi u7fff\r\n");
			uart_transmit(uart7, u7, 2);
		}
  }
}

void uart3_rx_callback_handel(struct device *uart3)
{
	uart_transmit(uart3, u3_rx, 1);
	uart_receive(uart3, u3_rx, 1);
}
