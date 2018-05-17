#ifndef __I2C_COMMON_API_H
#define __I2C_COMMON_API_H

#include "device.h"


               /*-----------API--------------*/
typedef int (*i2c_api_1)(struct device *dev, uint16_t addr, uint16_t reg, uint8_t *data, uint16_t length);
typedef int (*i2c_api_2)(struct device *dev, uint16_t addr, uint16_t reg, uint8_t *data, uint16_t length);

struct i2c_common_api {
	i2c_api_1 mem_write;
	i2c_api_2 mem_read;
};

               /*-----------APP--------------*/
static inline int i2c_init(struct device *dev)
{
	return dev->init(dev);
}

static inline int i2c_mem_write(struct device *dev, uint16_t addr, uint16_t reg, uint8_t *data, uint16_t length)
{
	const struct i2c_common_api *i2c_common_api = dev->api;
	return i2c_common_api->mem_write(dev, addr, reg, data, length);
}

static inline int i2c_mem_read(struct device *dev, uint16_t addr, uint16_t reg, uint8_t *data, uint16_t length)
{
	const struct i2c_common_api *i2c_common_api = dev->api;
	return i2c_common_api->mem_read(dev, addr, reg, data, length);
}


#endif
