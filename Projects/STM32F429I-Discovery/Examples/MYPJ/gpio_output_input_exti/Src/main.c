/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include "system_initialization.h"
#include "uart_printf.h"
#include "stm32f4xx_hal.h"
#include "api_define.h"
#include "gpio_a0.h"
#include "gpio_g13.h"
#include "main.h"


int main(void)
{
	system_initialization();
	uart_printf_init();
	
	struct gpio_api *gpio_a0  = gpio_a0_binding();
	struct gpio_api *gpio_g13 = gpio_g13_binding();
	gpio_a0->init();
	gpio_g13->init();
	
	#ifdef A0_EXTI
	while(1) {
	}
	#elif A0_INPUT
	while(1) {
		if(gpio_a0->read()) {
			gpio_g13->write(1);
			printf("PA0 STATE %d\r\n", gpio_a0->read());
			HAL_Delay(100);
		}else {
			gpio_g13->write(0);
			printf("PA0 STATE %d\r\n", gpio_a0->read());
			HAL_Delay(100);
		}
	}
	#endif
}
