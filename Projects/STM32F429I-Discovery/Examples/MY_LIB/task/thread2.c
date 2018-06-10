/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include <stdio.h>
#include "cmsis_os.h"
#include "thread2.h"

static osMessageQId osQueue;

void message_put(uint32_t msg)
{
	osMessagePut(osQueue, msg, osWaitForever);
}

static void Thread2(const void *argument)
{
	osEvent event;
	
	for(;;) {
		event = osMessageGet(osQueue, osWaitForever);
		
		if(event.status == osEventMessage) {
			struct message *p = (struct message*)event.value.p;
			printf("%s\r\n", p->name);
			printf("%d\r\n", p->age);
			printf("%f\r\n", p->height);
		}
	}
}

void thread2(void)
{
	osMessageQDef(osqueue, 2, struct message); //¦î¦Cªø«×¡B¦î¦C«¬ºA
	osQueue = osMessageCreate(osMessageQ(osqueue), NULL);

	osThreadDef(RxThread, Thread2, osPriorityNormal, 0, configMINIMAL_STACK_SIZE);
	osThreadCreate(osThread(RxThread), NULL);
}
