/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#ifndef __GPIO_COMMON_API_H
#define __GPIO_COMMON_API_H


enum count_unit {
	MILLISECOND,
	SECOND,
};

               /*-----------API--------------*/
typedef int (*gpio_api_1)(struct device *dev);
typedef void (*gpio_api_2)(struct device *dev, uint16_t state);
typedef void (*gpio_api_3)(struct device *dev);
typedef uint32_t (*gpio_api_4)(struct device *dev, enum count_unit unit);

struct gpio_common_api {
	gpio_api_1 read;
	gpio_api_2 write;
	gpio_api_3 toggle_write;
	gpio_api_4 counter_read;
};

               /*-----------APP--------------*/
static inline int gpio_init(struct device *dev)
{
	return dev->init(dev);
}

static inline int gpio_read(struct device *dev)
{
	const struct gpio_common_api *d_api = dev->api;
	return d_api->read(dev);
}

static inline void gpio_write(struct device *dev, uint16_t state)
{
	const struct gpio_common_api *d_api = dev->api;
	d_api->write(dev, state);
}

static inline void gpio_toggle_write(struct device *dev)
{
	const struct gpio_common_api *d_api = dev->api;
	d_api->toggle_write(dev);
}

static inline uint32_t gpio_counter_read(struct device *dev, enum count_unit unit)
{
	const struct gpio_common_api *d_api = dev->api;
	return d_api->counter_read(dev, unit);
}


#endif
