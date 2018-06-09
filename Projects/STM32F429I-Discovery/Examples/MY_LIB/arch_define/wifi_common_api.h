/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#ifndef __WIFI_COMMON_API_H
#define __WIFI_COMMON_API_H

#include "device.h"


               /*-----------API--------------*/
typedef int (*wifi_api_1)(struct device *dev);
typedef int (*wifi_api_2)(struct device *dev);

struct wifi_common_api {
	wifi_api_1 send;
	wifi_api_2 get;
};

               /*-----------APP--------------*/
static inline int wifi_init(struct device *dev)
{
	return dev->init(dev);
}

static inline int wifi_send(struct device *dev)
{
	const struct wifi_common_api *d_api = dev->api;
	return d_api->send(dev);
}

static inline int wifi_get(struct device *dev)
{
	const struct wifi_common_api *d_api = dev->api;
	return d_api->get(dev);
}


#endif
