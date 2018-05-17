#ifndef __GPIO_COMMON_API_H
#define __GPIO_COMMON_API_H

#include "device.h"


               /*-----------API--------------*/
typedef int (*gpio_api_1)(struct device *dev);
typedef void (*gpio_api_2)(struct device *dev, uint16_t state);
typedef void (*gpio_api_3)(struct device *dev);

struct gpio_common_api {
	gpio_api_1 read;
	gpio_api_2 write;
	gpio_api_3 toggle_write;
};

               /*-----------APP--------------*/
static inline int gpio_init(struct device *dev)
{
	return dev->init(dev);
}

static inline int gpio_read(struct device *dev)
{
	const struct gpio_common_api *gpio_common_api = dev->api;
	return gpio_common_api->read(dev);
}

static inline void gpio_write(struct device *dev, uint16_t state)
{
	const struct gpio_common_api *gpio_common_api = dev->api;
	gpio_common_api->write(dev, state);
}

static inline void gpio_toggle_write(struct device *dev)
{
	const struct gpio_common_api *gpio_common_api = dev->api;
	gpio_common_api->toggle_write(dev);
}


#endif
