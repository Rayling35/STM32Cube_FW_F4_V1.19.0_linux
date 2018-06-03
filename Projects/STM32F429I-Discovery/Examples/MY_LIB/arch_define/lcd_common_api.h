#ifndef __LCD_COMMON_API_H
#define __LCD_COMMON_API_H

#include "device.h"


               /*-----------API--------------*/
typedef void (*lcd_api_1)(struct device *dev, uint16_t select, uint8_t *number, uint16_t function);
typedef void (*lcd_api_2)(struct device *dev);
typedef void (*lcd_api_3)(struct device *dev);

struct lcd_common_api {
	lcd_api_1 show;
	lcd_api_2 set_all;
	lcd_api_3 clean_all;
};

               /*-----------APP--------------*/
static inline int lcd_init(struct device *dev)
{
	return dev->init(dev);
}

static inline void lcd_show(struct device *dev, uint16_t select, uint8_t *number, uint16_t function)
{
	const struct lcd_common_api *d_api = dev->api;
	d_api->show(dev, select, number, function);
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


#endif
