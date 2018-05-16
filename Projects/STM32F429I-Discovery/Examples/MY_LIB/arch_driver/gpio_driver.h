#ifndef __GPIO_DRIVER_H
#define __GPIO_DRIVER_H


#ifdef GPIO_A0_DEV
struct device* gpio_a0_device_binding(void);
#endif

#ifdef GPIO_G13_DEV
struct device* gpio_g13_device_binding(void);
#endif


#endif
