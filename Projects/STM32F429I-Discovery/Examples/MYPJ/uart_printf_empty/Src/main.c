#include "system_initialization.h"
#include "uart_printf.h"
#include "main.h"


int main(void)
{
	system_initialization();
	uart_printf_init();
	
	printf("Printf Empty Example\n\r");
}
