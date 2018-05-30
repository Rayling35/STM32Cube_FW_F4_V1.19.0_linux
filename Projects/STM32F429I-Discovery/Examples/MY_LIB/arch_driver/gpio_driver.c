#include "api_define.h"
#include "gpio_common_api.h"
#include "gpio_driver.h"


struct gpio_data {
	struct gpio_api *gpio_hal;
};

struct gpio_config {
	int config;
};

/*-----------API--------------*/
static int read_data(struct device *dev)
{
	struct gpio_data *data    = dev->data;
	struct gpio_api *gpio_hal = data->gpio_hal;
	
	return gpio_hal->read();
}

static void write_data(struct device *dev, uint16_t state)
{
	struct gpio_data *data    = dev->data;
	struct gpio_api *gpio_hal = data->gpio_hal;
	
	gpio_hal->write(state);
}

static void toggle_write_data(struct device *dev)
{
	struct gpio_data *data    = dev->data;
	struct gpio_api *gpio_hal = data->gpio_hal;
	
	gpio_hal->toggle_write();
}

static const struct gpio_common_api gpio_common_api = {
	.read  = read_data,
	.write = write_data,
	.toggle_write = toggle_write_data,
};


#ifdef GPIO_A0_DEV
#include "gpio_a0.h"
static struct gpio_data gpio_a0_data;
static const struct gpio_config gpio_a0_config;

static int gpio_a0_init(struct device *dev)
{
	struct gpio_data *data = dev->data;
	
	data->gpio_hal = gpio_a0_binding();
	data->gpio_hal->init();
	printf("GPIO_A0 device init\r\n");

	return 0;
}

struct device gpio_a0 = {
	.api    = &gpio_common_api,
	.data   = &gpio_a0_data,
	.config = &gpio_a0_config,
	.init   = gpio_a0_init,
};

struct device* gpio_a0_device_binding(void)
{
	return &gpio_a0;
}

__weak void a0_exit_handel(void)
{
}
#endif


#ifdef GPIO_A5_DEV
#include "gpio_a5.h"
static struct gpio_data gpio_a5_data;
static const struct gpio_config gpio_a5_config;

static int gpio_a5_init(struct device *dev)
{
	struct gpio_data *data = dev->data;
	
	data->gpio_hal = gpio_a5_binding();
	data->gpio_hal->init();
	printf("GPIO_A5 device init\r\n");

	return 0;
}

struct device gpio_a5 = {
	.api    = &gpio_common_api,
	.data   = &gpio_a5_data,
	.config = &gpio_a5_config,
	.init   = gpio_a5_init,
};

struct device* gpio_a5_device_binding(void)
{
	return &gpio_a5;
}

__weak void a5_exit_handel(void)
{
}
#endif


#ifdef GPIO_C1_DEV
#include "gpio_c1.h"
static struct gpio_data gpio_c1_data;
static const struct gpio_config gpio_c1_config;

static int gpio_c1_init(struct device *dev)
{
	struct gpio_data *data = dev->data;
	
	data->gpio_hal = gpio_c1_binding();
	data->gpio_hal->init();
	printf("GPIO_C1 device init\r\n");

	return 0;
}

struct device gpio_c1 = {
	.api    = &gpio_common_api,
	.data   = &gpio_c1_data,
	.config = &gpio_c1_config,
	.init   = gpio_c1_init,
};

struct device* gpio_c1_device_binding(void)
{
	return &gpio_c1;
}

__weak void c1_exit_handel(void)
{
}
#endif


#ifdef GPIO_G2_DEV
#include "gpio_g2.h"
static struct gpio_data gpio_g2_data;
static const struct gpio_config gpio_g2_config;

static int gpio_g2_init(struct device *dev)
{
	struct gpio_data *data = dev->data;
	
	data->gpio_hal = gpio_g2_binding();
	data->gpio_hal->init();
	printf("GPIO_G2 device init\r\n");

	return 0;
}

struct device gpio_g2 = {
	.api    = &gpio_common_api,
	.data   = &gpio_g2_data,
	.config = &gpio_g2_config,
	.init   = gpio_g2_init,
};

struct device* gpio_g2_device_binding(void)
{
	return &gpio_g2;
}

__weak void g2_exit_handel(void)
{
}
#endif


#ifdef GPIO_G3_DEV
#include "gpio_g3.h"
static struct gpio_data gpio_g3_data;
static const struct gpio_config gpio_g3_config;

static int gpio_g3_init(struct device *dev)
{
	struct gpio_data *data = dev->data;
	
	data->gpio_hal = gpio_g3_binding();
	data->gpio_hal->init();
	printf("GPIO_G3 device init\r\n");

	return 0;
}

struct device gpio_g3 = {
	.api    = &gpio_common_api,
	.data   = &gpio_g3_data,
	.config = &gpio_g3_config,
	.init   = gpio_g3_init,
};

struct device* gpio_g3_device_binding(void)
{
	return &gpio_g3;
}

__weak void g3_exit_handel(void)
{
}
#endif


#ifdef GPIO_G13_DEV
#include "gpio_g13.h"
static struct gpio_data gpio_g13_data;
static const struct gpio_config gpio_g13_config;

static int gpio_g13_init(struct device *dev)
{
	struct gpio_data *data = dev->data;
	
	data->gpio_hal = gpio_g13_binding();
	data->gpio_hal->init();
	printf("GPIO_G13 device init\r\n");

	return 0;
}

struct device gpio_g13 = {
	.api    = &gpio_common_api,
	.data   = &gpio_g13_data,
	.config = &gpio_g13_config,
	.init   = gpio_g13_init,
};

struct device* gpio_g13_device_binding(void)
{
	return &gpio_g13;
}

__weak void g13_exit_handel(void)
{
}
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
		a0_exit_handel();
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
