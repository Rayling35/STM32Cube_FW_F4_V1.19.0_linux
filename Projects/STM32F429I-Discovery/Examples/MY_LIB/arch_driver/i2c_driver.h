#ifndef __I2C_DRIVER_H
#define __I2C_DRIVER_H


#ifdef I2C1_DEV
struct device* i2c1_device_binding(void);
#endif

#ifdef I2C3_DEV
struct device* i2c3_device_binding(void);
#endif


#endif
