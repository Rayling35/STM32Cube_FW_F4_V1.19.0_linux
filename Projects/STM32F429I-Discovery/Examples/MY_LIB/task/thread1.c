#include <stdio.h>
#include "thread1.h"
#include "thread2.h"

static struct message meter = {
	.name = "rock man",
	.age = 88,
	.height = 251.36
};

static void Thread1(const void *argument)
{
	message_put((uint32_t)&meter);
}

void thread1(void)
{
	osThreadDef(TxThread, Thread1, osPriorityBelowNormal, 0, configMINIMAL_STACK_SIZE);
	osThreadCreate(osThread(TxThread), NULL);
}
