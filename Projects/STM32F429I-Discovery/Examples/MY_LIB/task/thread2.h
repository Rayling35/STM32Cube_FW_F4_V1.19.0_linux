/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#ifndef __THREAD2_H
#define __THREAD2_H

#include "cmsis_os.h"

struct message {
	char *name;
	uint16_t age;
	float height;
};


void message_put(uint32_t msg);
void thread2(void);

#endif
