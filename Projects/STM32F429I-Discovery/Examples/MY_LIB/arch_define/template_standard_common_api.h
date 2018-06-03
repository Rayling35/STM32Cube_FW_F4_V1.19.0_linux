#ifndef __TEMPLATE_STANDARD_COMMON_API_H
#define __TEMPLATE_STANDARD_COMMON_API_H

#include "device.h"


               /*-----------API--------------*/
typedef int (*standard_api_1)(struct device *dev);
typedef int (*standard_api_2)(struct device *dev);

struct standard_common_api {
	standard_api_1 send;
	standard_api_2 get;
};

               /*-----------APP--------------*/
static inline int standard_init(struct device *dev)
{
	return dev->init(dev);
}

static inline int standard_app1(struct device *dev)
{
	const struct standard_common_api *d_api = dev->api;
	return d_api->send(dev);
}

static inline int standard_app2(struct device *dev)
{
	const struct standard_common_api *d_api = dev->api;
	return d_api->get(dev);
}


#endif
