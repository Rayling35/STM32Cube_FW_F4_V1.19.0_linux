#include "thread2.h"

static osMessageQId osQueue;

void message_put(uint16_t msg)
{
	osMessagePut(osQueue, msg, 0);
}


static void Thread2 (const void *argument)
{
	osEvent event;
	
	for(;;) {
		event = osMessageGet(osQueue, osWaitForever);
		if(event.status == osEventMessage) {
			if(event.value.v == 100) {
				printf("100\r\n");
			}else {
				printf("99\r\n");
			}
		}
	}
}

void r_queue(void)
{
	osMessageQDef(osqueue, 1, uint16_t);
	osQueue = osMessageCreate(osMessageQ(osqueue), NULL);

	osThreadDef(RxThread, Thread2, osPriorityNormal, 0, configMINIMAL_STACK_SIZE);
	osThreadCreate(osThread(RxThread), NULL);
}
