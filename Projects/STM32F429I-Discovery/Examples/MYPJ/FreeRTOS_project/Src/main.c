#include "main.h"


int main(void)
{
	system_initialization();
	uart_printf_init();
	
	r_thread();
	r_queue();
	
	osKernelStart();
	
	for(;;);
}
