#include "api_define.h"
#include "i2c_common_api.h"
#include "i2c_driver.h"


struct i2c_data {
	struct i2c_api *i2c_hal;
};

struct i2c_config {
	uint32_t write_timeout;
	uint32_t read_timeout;
};


/*-----------API--------------*/
static int mem_write_data(struct device *dev, uint16_t addr, uint16_t reg, uint8_t *w_data, uint16_t length)
{
	struct i2c_data *d_data           = dev->data;
	const struct i2c_config *d_config = dev->config;
	struct i2c_api *i2c_hal           = d_data->i2c_hal;
	
	return i2c_hal->mem_write(addr, reg, w_data, length, d_config->write_timeout);
}

static int mem_read_data(struct device *dev, uint16_t addr, uint16_t reg, uint8_t *r_data, uint16_t length)
{
	struct i2c_data *d_data           = dev->data;
	const struct i2c_config *d_config = dev->config;
	struct i2c_api *i2c_hal           = d_data->i2c_hal;
	
	return i2c_hal->mem_read(addr, reg, r_data, length, d_config->read_timeout);
}

static const struct i2c_common_api i2c_common_api = {
	.mem_write = mem_write_data,
	.mem_read  = mem_read_data,
};


#ifdef I2C1_DEV
#include "i2c1.h"
static struct i2c_data i2c1_data;

static const struct i2c_config i2c1_config = {
	.write_timeout = 1,
	.read_timeout  = 1,
};

static int i2c1_dev_init(struct device *dev)
{
	struct i2c_data *d_data = dev->data;
	
	d_data->i2c_hal = i2c1_binding();
	d_data->i2c_hal->init();
	printf("I2C1 device init\r\n");
	
	return 0;
}

struct device i2c_1 = {
	.api    = &i2c_common_api,
	.data   = &i2c1_data,
	.config = &i2c1_config,
	.init   = i2c1_dev_init,
};

struct device* i2c1_device_binding(void)
{
	return &i2c_1;
}
#endif

#ifdef I2C3_DEV
#include "i2c3.h"
static struct i2c_data i2c3_data;

static const struct i2c_config i2c3_config = {
	.write_timeout = 1,
	.read_timeout  = 1,
};

static int i2c3_dev_init(struct device *dev)
{
	struct i2c_data *d_data = dev->data;
	
	d_data->i2c_hal = i2c3_binding();
	d_data->i2c_hal->init();
	printf("I2C3 device init\r\n");
	
	return 0;
}

struct device i2c_3 = {
	.api    = &i2c_common_api,
	.data   = &i2c3_data,
	.config = &i2c3_config,
	.init   = i2c3_dev_init,
};

struct device* i2c3_device_binding(void)
{
	return &i2c_3;
}
#endif
