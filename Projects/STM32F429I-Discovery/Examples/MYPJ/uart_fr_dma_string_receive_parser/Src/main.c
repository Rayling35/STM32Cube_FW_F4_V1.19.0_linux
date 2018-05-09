#include "system_initialization.h"
#include "uart_printf.h"
#include "cmsis_os.h"
#include "main.h"

#include "api_define.h"
#include "uart6.h"
#include "task_dma_parser.h"

#include "uart7.h"
#include "task_test.h"


int main(void)
{
	system_initialization();
	uart_printf_init();
	
	
	struct uart_api *uart6 = uart6_binding();
	uart6->init();
	task_dma_parser(uart6);
	
	struct uart_api *uart7 = uart7_binding();
	uart7->init();
	task_test(uart7);
	
	
	osKernelStart();
	for(;;);
}
