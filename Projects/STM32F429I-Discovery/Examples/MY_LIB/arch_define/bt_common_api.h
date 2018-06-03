#ifndef __BT_COMMON_API_H
#define __BT_COMMON_API_H

#include "device.h"


               /*-----------API--------------*/
typedef int (*bt_api_1)(struct device *dev);
typedef int (*bt_api_2)(struct device *dev);

struct bt_common_api {
	bt_api_1 send;
	bt_api_2 get;
};

               /*-----------APP--------------*/
static inline int bt_init(struct device *dev)
{
	return dev->init(dev);
}

static inline int bt_send(struct device *dev)
{
	const struct bt_common_api *d_api = dev->api;
	return d_api->send(dev);
}

static inline int bt_get(struct device *dev)
{
	const struct bt_common_api *d_api = dev->api;
	return d_api->get(dev);
}


#endif
