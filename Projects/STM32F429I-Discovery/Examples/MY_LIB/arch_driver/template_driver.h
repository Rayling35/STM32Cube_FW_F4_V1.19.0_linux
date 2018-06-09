#ifndef __TEMPLATE_DRIVER_H
#define __TEMPLATE_DRIVER_H

#include "stm32f4xx_hal.h"


struct template_data {
	struct device *binding_device_1;
	struct device *binding_device_2;
	int data1;
	int data2;
};

struct template_config {
	uint32_t this_config_1;
	uint32_t this_config_2;
};

struct device* template_device_binding(void);


#endif
