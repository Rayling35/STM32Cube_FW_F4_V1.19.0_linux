/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include "stm32f4xx_hal.h"
#include "cmsis_os.h"
#include "device.h"
#include "gpio_driver.h"
#include "gpio_common_api.h"
#include "button_event_driver.h"
#include "button_event_common_api.h"


static uint8_t status_get(struct device *dev, enum button_select button)
{
	struct button_event_data *d_data = dev->data;
	
	switch (button) {
		case GPIO_A0:
			return d_data->flag_a0;
		case GPIO_A0_5_SEC:
			return d_data->flag_a0_5sec;
		case GPIO_A0_10_SEC:
			return d_data->flag_a0_10sec;
//		case GPIO_A1:
//			return d_data->flag_a1;
//		case GPIO_A2:
//			return d_data->flag_a2;
//		case GPIO_A3:
//			return d_data->flag_a3;
//		case GPIO_A4:
//			return d_data->flag_a4;
//		case GPIO_A5:
//			return d_data->flag_a5;
		default:
			return 0;
	}
}

static const struct button_event_common_api button_event_api = {
	.status_get = status_get,
};

static void button_counter_thread(const void *argument)
{
	struct button_event_data *d_data = (struct button_event_data *)argument;
	struct device *gpio              = d_data->gpio_a0;
	int no_trigger_status;
	uint32_t count;
	
	no_trigger_status = gpio_read(gpio);
	
	while(1) {
		if(gpio_read(gpio) != no_trigger_status) {
			count = 0;
			do {
				HAL_Delay(100);
				count++;
				if(count == 50) {
					d_data->flag_a0_5sec = 1;
				}
				if(count == 100) {
					d_data->flag_a0_10sec = 1;
				}
			}while(gpio_read(gpio) != no_trigger_status);
		}
		d_data->flag_a0_5sec = 0;
		d_data->flag_a0_10sec = 0;
	}
}

static void button_monitor_thread(const void *argument)
{
	struct button_event_data *d_data = (struct button_event_data *)argument;
	
	while(1) {
		d_data->flag_a0 = gpio_read(d_data->gpio_a0);
//		d_data->flag_a1 = gpio_read(d_data->gpio_a1);
//		d_data->flag_a2 = gpio_read(d_data->gpio_a2);
//		d_data->flag_a3 = gpio_read(d_data->gpio_a3);
//		d_data->flag_a4 = gpio_read(d_data->gpio_a4);
//		d_data->flag_a5 = gpio_read(d_data->gpio_a5);
	}
}

static struct button_event_data button_event_data;

static int button_event_dev_init(struct device *dev)
{
	struct button_event_data *d_data = dev->data;
	
	d_data->gpio_a0 = gpio_a0_device_binding();
//	d_data->gpio_a1 = gpio_a1_device_binding();
//	d_data->gpio_a2 = gpio_a2_device_binding();
//	d_data->gpio_a3 = gpio_a3_device_binding();
//	d_data->gpio_a4 = gpio_a4_device_binding();
//	d_data->gpio_a5 = gpio_a5_device_binding();
	gpio_init(d_data->gpio_a0);
//	gpio_init(d_data->gpio_a1);
//	gpio_init(d_data->gpio_a2);
//	gpio_init(d_data->gpio_a3);
//	gpio_init(d_data->gpio_a4);
//	gpio_init(d_data->gpio_a5);
	
	osThreadDef(button_monitor, button_monitor_thread, osPriorityNormal, 0, configMINIMAL_STACK_SIZE);
	osThreadCreate(osThread(button_monitor), d_data);
	
	osThreadDef(button_counter, button_counter_thread, osPriorityNormal, 0, configMINIMAL_STACK_SIZE);
	osThreadCreate(osThread(button_counter), d_data);
	
	printf("Button Event device init\r\n");
	return 0;
}

struct device button_event = {
	.api  = &button_event_api,
	.data = &button_event_data,
	.init = button_event_dev_init,
};

struct device* button_event_device_binding(void)
{
	return &button_event;
}
