/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#ifndef __BUTTON_EVENT_DRIVER_H
#define __BUTTON_EVENT_DRIVER_H


struct button_event_data {
	struct device *gpio_a0; //button 1
//	struct device *gpio_a1; //button 2
//	struct device *gpio_a2; //button 3
//	struct device *gpio_a3; //button 4
//	struct device *gpio_a4; //button 5
//	struct device *gpio_a5; //button 6
	
	uint8_t flag_a0;
	uint8_t flag_a0_5sec;
	uint8_t flag_a0_10sec;
//	uint8_t flag_a1;
//	uint8_t flag_a2;
//	uint8_t flag_a3;
//	uint8_t flag_a4;
//	uint8_t flag_a5;
};

struct device* button_event_device_binding(void);


#endif
