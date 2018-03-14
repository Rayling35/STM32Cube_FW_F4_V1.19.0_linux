#include "main.h"

osThreadId Thread1Handle;
osThreadId Thread2Handle;

static void Thread1(void const *argument)
{
  uint32_t count = 0;
  (void)argument;
  
  for(;;)
  {
    count = osKernelSysTick() + 5000;
    while (count >= osKernelSysTick()) {
			printf("Thread1\r\n");
      osDelay(200);
    }
    osThreadSuspend(NULL);
    count = osKernelSysTick() + 5000;
    while (count >= osKernelSysTick()) {
			printf("Thread1\r\n");
      osDelay(400);
    }
    osThreadResume(Thread2Handle);
  }
}

static void Thread2(void const *argument)
{
  uint32_t count;
  (void)argument;
  
  for(;;)
  {
    count = osKernelSysTick() + 10000;
    while (count >= osKernelSysTick()) {
			printf("Thread2\r\n");
      osDelay(500);
    }
    osThreadResume(Thread1Handle);
    osThreadSuspend(NULL);  
  }
}

int main(void)
{
  system_initialization();
	uart_printf_init();
  
  osThreadDef(TX1, Thread1, osPriorityNormal, 0, configMINIMAL_STACK_SIZE);
  Thread1Handle = osThreadCreate (osThread(TX1), NULL);
	
  osThreadDef(TX2, Thread2, osPriorityNormal, 0, configMINIMAL_STACK_SIZE);
  Thread2Handle = osThreadCreate (osThread(TX2), NULL);
	
  osKernelStart();
	
  for(;;);
}
