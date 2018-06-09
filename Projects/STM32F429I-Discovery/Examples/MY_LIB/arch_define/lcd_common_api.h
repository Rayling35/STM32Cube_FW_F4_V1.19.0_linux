/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#ifndef __LCD_COMMON_API_H
#define __LCD_COMMON_API_H

#include "device.h"


               /*-----------API--------------*/
typedef void (*lcd_api_1)(struct device *dev);
typedef void (*lcd_api_2)(struct device *dev);

#ifdef PZ_LCD
typedef void (*lcd_api_pz_1)(struct device *dev, uint16_t value);
typedef void (*lcd_api_pz_2)(struct device *dev, float value);
typedef void (*lcd_api_pz_3)(struct device *dev, float value);
typedef void (*lcd_api_pz_4)(struct device *dev, uint32_t value);
#endif

struct lcd_common_api {
	lcd_api_1 set_all;
	lcd_api_2 clean_all;
	
	#ifdef PZ_LCD
	lcd_api_pz_1 voltage;
	lcd_api_pz_2 current;
	lcd_api_pz_3 power;
	lcd_api_pz_4 consumption;
	#endif
};

               /*-----------APP--------------*/
static inline int lcd_init(struct device *dev)
{
	return dev->init(dev);
}

static inline void lcd_set_all(struct device *dev)
{
	const struct lcd_common_api *d_api = dev->api;
	d_api->set_all(dev);
}

static inline void lcd_clean_all(struct device *dev)
{
	const struct lcd_common_api *d_api = dev->api;
	d_api->clean_all(dev);
}

#ifdef PZ_LCD
static inline void pz_voltage(struct device *dev, uint16_t value)
{
	const struct lcd_common_api *d_api = dev->api;
	d_api->voltage(dev, value);
}

static inline void pz_current(struct device *dev, float value)
{
	const struct lcd_common_api *d_api = dev->api;
	d_api->current(dev, value);
}

static inline void pz_power(struct device *dev, float value)
{
	const struct lcd_common_api *d_api = dev->api;
	d_api->power(dev, value);
}

static inline void pz_consumption(struct device *dev, uint32_t value)
{
	const struct lcd_common_api *d_api = dev->api;
	d_api->consumption(dev, value);
}
#endif


#endif
