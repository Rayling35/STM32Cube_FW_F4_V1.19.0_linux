/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include "stm32f4xx_hal.h"
#include "device.h"
#include "api_define.h"
#include "gpio_driver.h"
#include "gpio_common_api.h"


static int read_data(struct device *dev)
{
	struct gpio_data *d_data  = dev->data;
	struct gpio_api *gpio_hal = d_data->gpio_hal;
	
	return gpio_hal->read();
}

static void write_data(struct device *dev, uint16_t state)
{
	struct gpio_data *d_data  = dev->data;
	struct gpio_api *gpio_hal = d_data->gpio_hal;
	
	gpio_hal->write(state);
}

static void toggle_write_data(struct device *dev)
{
	struct gpio_data *d_data  = dev->data;
	struct gpio_api *gpio_hal = d_data->gpio_hal;
	
	gpio_hal->toggle_write();
}

static const struct gpio_common_api gpio_common_api = {
	.read         = read_data,
	.write        = write_data,
	.toggle_write = toggle_write_data,
};


#ifdef GPIO_A0_DEV
#include "gpio_a0.h"
static struct gpio_data gpio_a0_data;

static int gpio_a0_dev_init(struct device *dev)
{
	struct gpio_data *d_data = dev->data;
	
	d_data->gpio_hal = gpio_a0_binding();
	d_data->gpio_hal->init();
	printf("GPIO_A0 device init\r\n");

	return 0;
}

struct device gpio_a0 = {
	.api    = &gpio_common_api,
	.data   = &gpio_a0_data,
	.init   = gpio_a0_dev_init,
};

struct device* gpio_a0_device_binding(void)
{
	return &gpio_a0;
}

#ifdef A0_EXIT
__weak void a0_exit_handel(void)
{
}
#endif
#endif


#ifdef GPIO_A5_DEV
#include "gpio_a5.h"
static struct gpio_data gpio_a5_data;

static int gpio_a5_dev_init(struct device *dev)
{
	struct gpio_data *d_data = dev->data;
	
	d_data->gpio_hal = gpio_a5_binding();
	d_data->gpio_hal->init();
	printf("GPIO_A5 device init\r\n");

	return 0;
}

struct device gpio_a5 = {
	.api    = &gpio_common_api,
	.data   = &gpio_a5_data,
	.init   = gpio_a5_dev_init,
};

struct device* gpio_a5_device_binding(void)
{
	return &gpio_a5;
}

#ifdef A5_EXIT
__weak void a5_exit_handel(void)
{
}
#endif
#endif


#ifdef GPIO_C1_DEV
#include "gpio_c1.h"
static struct gpio_data gpio_c1_data;

static int gpio_c1_dev_init(struct device *dev)
{
	struct gpio_data *d_data = dev->data;
	
	d_data->gpio_hal = gpio_c1_binding();
	d_data->gpio_hal->init();
	printf("GPIO_C1 device init\r\n");

	return 0;
}

struct device gpio_c1 = {
	.api    = &gpio_common_api,
	.data   = &gpio_c1_data,
	.init   = gpio_c1_dev_init,
};

struct device* gpio_c1_device_binding(void)
{
	return &gpio_c1;
}

#ifdef C1_EXIT
__weak void c1_exit_handel(void)
{
}
#endif
#endif


#ifdef GPIO_G2_DEV
#include "gpio_g2.h"
static struct gpio_data gpio_g2_data;

static int gpio_g2_dev_init(struct device *dev)
{
	struct gpio_data *d_data = dev->data;
	
	d_data->gpio_hal = gpio_g2_binding();
	d_data->gpio_hal->init();
	printf("GPIO_G2 device init\r\n");

	return 0;
}

struct device gpio_g2 = {
	.api    = &gpio_common_api,
	.data   = &gpio_g2_data,
	.init   = gpio_g2_dev_init,
};

struct device* gpio_g2_device_binding(void)
{
	return &gpio_g2;
}

#ifdef G2_EXIT
__weak void g2_exit_handel(void)
{
}
#endif
#endif


#ifdef GPIO_G3_DEV
#include "gpio_g3.h"
static struct gpio_data gpio_g3_data;

static int gpio_g3_dev_init(struct device *dev)
{
	struct gpio_data *d_data = dev->data;
	
	d_data->gpio_hal = gpio_g3_binding();
	d_data->gpio_hal->init();
	printf("GPIO_G3 device init\r\n");

	return 0;
}

struct device gpio_g3 = {
	.api    = &gpio_common_api,
	.data   = &gpio_g3_data,
	.init   = gpio_g3_dev_init,
};

struct device* gpio_g3_device_binding(void)
{
	return &gpio_g3;
}

#ifdef G3_EXIT
__weak void g3_exit_handel(void)
{
}
#endif
#endif


#ifdef GPIO_G13_DEV
#include "gpio_g13.h"
static struct gpio_data gpio_g13_data;

static int gpio_g13_dev_init(struct device *dev)
{
	struct gpio_data *d_data = dev->data;
	
	d_data->gpio_hal = gpio_g13_binding();
	d_data->gpio_hal->init();
	printf("GPIO_G13 device init\r\n");

	return 0;
}

struct device gpio_g13 = {
	.api    = &gpio_common_api,
	.data   = &gpio_g13_data,
	.init   = gpio_g13_dev_init,
};

struct device* gpio_g13_device_binding(void)
{
	return &gpio_g13;
}

#ifdef G13_EXIT
__weak void g13_exit_handel(void)
{
}
#endif
#endif


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	#ifdef A0_EXIT
	if(GPIO_Pin == GPIO_PIN_0) {
		a0_exit_handel();
	}
	#endif
	
	#ifdef A5_EXIT
	if(GPIO_Pin == GPIO_PIN_5) {
		a5_exit_handel();
	}
	#endif
	
	#ifdef C1_EXIT
	if(GPIO_Pin == GPIO_PIN_1) {
		c1_exit_handel();
	}
	#endif
	
	#ifdef G2_EXIT
	if(GPIO_Pin == GPIO_PIN_2) {
		g2_exit_handel();
	}
	#endif
	
	#ifdef G3_EXIT
	if(GPIO_Pin == GPIO_PIN_3) {
		g3_exit_handel();
	}
	#endif
	
	#ifdef G13_EXIT
	if(GPIO_Pin == GPIO_PIN_13) {
		g13_exit_handel();
	}
	#endif
}
