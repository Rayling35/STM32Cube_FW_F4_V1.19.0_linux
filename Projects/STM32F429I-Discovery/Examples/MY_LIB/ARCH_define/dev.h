#ifndef _dev_H_
#define _dev_H_

#include "stm32f4xx_hal.h"

struct device {
	const void *api;
	void *data;
	const void *config;
	int (*init)(struct device *dev);
};

#endif
