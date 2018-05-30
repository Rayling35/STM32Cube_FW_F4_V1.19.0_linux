#ifndef __GPIO_DRIVER_H
#define __GPIO_DRIVER_H


#ifdef GPIO_A0_DEV
#include "gpio_a0.h"
struct device* gpio_a0_device_binding(void);
#endif

#ifdef GPIO_A5_DEV
#include "gpio_a5.h"
struct device* gpio_a5_device_binding(void);
#endif

#ifdef GPIO_C1_DEV
#include "gpio_c1.h"
struct device* gpio_c1_device_binding(void);
#endif

#ifdef GPIO_G2_DEV
#include "gpio_g2.h"
struct device* gpio_g2_device_binding(void);
#endif

#ifdef GPIO_G3_DEV
#include "gpio_g3.h"
struct device* gpio_g3_device_binding(void);
#endif

#ifdef GPIO_G13_DEV
#include "gpio_g13.h"
struct device* gpio_g13_device_binding(void);
#endif


#endif
