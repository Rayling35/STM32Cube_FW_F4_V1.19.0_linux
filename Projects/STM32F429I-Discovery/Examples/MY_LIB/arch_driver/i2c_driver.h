#ifndef __I2C_DRIVER_H
#define __I2C_DRIVER_H


struct i2c_data {
	struct i2c_api *i2c_hal;
};

struct i2c_config {
	uint32_t write_timeout;
	uint32_t read_timeout;
};

#ifdef I2C1_DEV
struct device* i2c1_device_binding(void);
#endif

#ifdef I2C3_DEV
struct device* i2c3_device_binding(void);
#endif


#endif
