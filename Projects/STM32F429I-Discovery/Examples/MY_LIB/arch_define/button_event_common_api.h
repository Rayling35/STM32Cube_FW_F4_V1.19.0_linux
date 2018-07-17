/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#ifndef __BUTTON_EVENT_COMMON_API_H
#define __BUTTON_EVENT_COMMON_API_H


enum button_select {
	GPIO_A0,
	GPIO_A0_5_SEC,
	GPIO_A0_10_SEC,
//	GPIO_A1,
//	GPIO_A2,
//	GPIO_A3,
//	GPIO_A4,
//	GPIO_A5,
};

               /*-----------API--------------*/
typedef uint8_t (*button_event_api_1)(struct device *dev, enum button_select button);

struct button_event_common_api {
	button_event_api_1 status_get;
};

               /*-----------APP--------------*/
static inline int button_event_init(struct device *dev)
{
	return dev->init(dev);
}

static inline uint8_t button_status_get(struct device *dev, enum button_select button)
{
	const struct button_event_common_api *d_api = dev->api;
	return d_api->status_get(dev, button);
}


#endif
