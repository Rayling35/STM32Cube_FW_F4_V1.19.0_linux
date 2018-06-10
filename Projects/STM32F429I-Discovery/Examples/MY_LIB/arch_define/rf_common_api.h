/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#ifndef __RF_COMMON_API_H
#define __RF_COMMON_API_H


               /*-----------API--------------*/
typedef int (*rf_api_1)(struct device *dev);
typedef int (*rf_api_2)(struct device *dev);

struct rf_common_api {
	rf_api_1 device_test;
	rf_api_2 get;
};

               /*-----------APP--------------*/
static inline int rf_init(struct device *dev)
{
	return dev->init(dev);
}

static inline int rf_device_test(struct device *dev)
{
	const struct rf_common_api *d_api = dev->api;
	return d_api->device_test(dev);
}

static inline int rf_get(struct device *dev)
{
	const struct rf_common_api *d_api = dev->api;
	return d_api->get(dev);
}


#endif
