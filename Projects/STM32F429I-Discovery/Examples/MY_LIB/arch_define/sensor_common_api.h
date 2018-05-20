#ifndef __SENSOR_COMMON_API_H
#define __SENSOR_COMMON_API_H

#include "device.h"


               /*-----------API--------------*/
typedef int (*sensor_api_1)(struct device *dev);
typedef int (*sensor_api_2)(struct device *dev);

struct sensor_common_api {
	sensor_api_1 send;
	sensor_api_2 get;
};

               /*-----------APP--------------*/
static inline int sensor_init(struct device *dev)
{
	return dev->init(dev);
}

static inline int sensor_send(struct device *dev)
{
	const struct sensor_common_api *sensor_common_api = dev->api;
	return sensor_common_api->send(dev);
}

static inline int sensor_get(struct device *dev)
{
	const struct sensor_common_api *sensor_common_api = dev->api;
	return sensor_common_api->get(dev);
}


#endif
