#include <dev.h>
#include <uart_api.h>
#include "system_initialization.h"
#include "uart_printf.h"
#include "main.h"
#include "uart.h"


int main(void)
{
	struct device *uart3 = (struct device *)uart3_binding();
	system_initialization();
	uart_printf_init();
	uart3->init(uart3);	
/*----------------------------*/

	uint8_t tx[] = "uart3_txxx";
	uint8_t rx[10];
	
	uart_write(uart3, tx, 10);
	HAL_Delay(200);
	printf("Hi\r\n");
	uart_read(uart3, rx, 10);
	printf("rx=%s\r\n", rx);
}
