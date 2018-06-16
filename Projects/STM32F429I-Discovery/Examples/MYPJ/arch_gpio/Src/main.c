/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include "system_initialization.h"
#include "uart_printf.h"
#include "stm32f4xx_hal.h"
#include "device.h"
#include "gpio_driver.h"
#include "gpio_common_api.h"
#include "main.h"


int main(void)
{
	system_initialization();
	uart_printf_init();
	
	struct device *gpio_a0 = gpio_a0_device_binding();
	struct device *gpio_g13 = gpio_g13_device_binding();
	gpio_init(gpio_a0);
	gpio_init(gpio_g13);
	printf("GPIO device init\r\n");
	
	#ifdef A0_EXTI
	while(1) {
	}
	#elif A0_INPUT
	while(1) {
		if(gpio_read(gpio_a0)) {
			gpio_write(gpio_g13, 1);
			printf("PA0 STATE %d\n\r", gpio_read(gpio_a0));
			HAL_Delay(100);
		}else {
			gpio_write(gpio_g13, 0);
			printf("PA0 STATE %d\n\r", gpio_read(gpio_a0));
			HAL_Delay(100);
		}
	}
	#endif
}

void a0_exti_handel(void)
{
	struct device *gpio_g13 = gpio_g13_device_binding();
	gpio_toggle_write(gpio_g13);
}
