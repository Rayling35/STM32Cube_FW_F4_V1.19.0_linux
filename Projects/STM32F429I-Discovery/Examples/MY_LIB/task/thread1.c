#include "thread1.h"


static void Thread1 (const void *argument)
{
	for(;;) {
		osDelay(500);
		message_put(100);
		printf("MessagePut\r\n");
	}
}

void r_thread(void)
{
	osThreadDef(TxThread, Thread1, osPriorityBelowNormal, 0, configMINIMAL_STACK_SIZE);
	osThreadCreate(osThread(TxThread), NULL);
}
