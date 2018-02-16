#ifndef _dev_H_
#define _dev_H_

#include "stdio.h"

struct device {
	void *data;
	const void *api;
	const void *config;
	int (*init)(struct device *dev);
};

#endif
