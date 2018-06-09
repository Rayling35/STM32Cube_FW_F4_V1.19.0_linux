/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#ifndef __DEVICE_H
#define __DEVICE_H

#include "stm32f4xx_hal.h"


struct device {
	const void *api;
	void *data;
	const void *config;
	int (*init)(struct device *dev);
};


#endif
