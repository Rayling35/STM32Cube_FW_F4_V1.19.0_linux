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
#endif


__weak void a0_exit_handel(void)
{
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	#ifdef A0_EXIT
	if(GPIO_Pin == GPIO_PIN_0) {
		a0_exit_handel();
	}
	#endif
}
