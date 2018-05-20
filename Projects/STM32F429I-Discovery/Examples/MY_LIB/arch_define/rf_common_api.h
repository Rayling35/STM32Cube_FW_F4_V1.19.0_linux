#ifndef __RF_COMMON_API_H
#define __RF_COMMON_API_H

#include "device.h"


               /*-----------API--------------*/
typedef int (*rf_api_1)(struct device *dev);
typedef int (*rf_api_2)(struct device *dev);

struct rf_common_api {
	rf_api_1 send;
	rf_api_2 get;
};

               /*-----------APP--------------*/
static inline int rf_init(struct device *dev)
{
	return dev->init(dev);
}

static inline int rf_send(struct device *dev)
{
	const struct rf_common_api *rf_common_api = dev->api;
	return rf_common_api->send(dev);
}

static inline int rf_get(struct device *dev)
{
	const struct rf_common_api *rf_common_api = dev->api;
	return rf_common_api->get(dev);
}


#endif
