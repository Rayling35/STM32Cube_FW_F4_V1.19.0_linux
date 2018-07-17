/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include "system_initialization.h"
#include "uart_printf.h"
#include "stm32f4xx_hal.h"
#include "cmsis_os.h"
#include "device.h"
#include "button_event_driver.h"
#include "button_event_common_api.h"
#include "main.h"


static void main_thread(const void *button_event)
{
	struct device *button = (struct device *)button_event;
	
	while(1) {
		if(button_status_get(button, GPIO_A0)) {
			printf("GPIO_A0\r\n");
		}
		if(button_status_get(button, GPIO_A0_5_SEC)) {
			printf("GPIO_A0_5_SEC\r\n");
		}
		if(button_status_get(button, GPIO_A0_10_SEC)) {
			printf("GPIO_A0_10_SEC\r\n");
		}
	}
}

int main(void)
{
	system_initialization();
	uart_printf_init();
	
	struct device *button_event = button_event_device_binding();
	
	button_event_init(button_event);
	printf("All device init\r\n");
	
	osThreadDef(main, main_thread, osPriorityNormal, 0, configMINIMAL_STACK_SIZE);
	osThreadCreate(osThread(main), button_event);
	
	osKernelStart();
	while(1) {
	}
}
