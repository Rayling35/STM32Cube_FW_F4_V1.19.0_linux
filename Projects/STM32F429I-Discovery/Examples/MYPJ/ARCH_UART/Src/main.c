#include <dev.h>
#include <uart_api.h>
#include "main.h"

extern struct device uart_3;
struct device *uart3 = &uart_3;

int main(void)
{
	system_initialization();
	uart_printf_init();
	uart3->init(uart3);	
/*----------------------------*/

	uint8_t tx[] = "uart3_txxx";
	uint8_t rx[10];
	
	uart_write(uart3, tx, 10);
	HAL_Delay(200);
	uart_read(uart3, rx, 10);
	printf("rx=%s\r\n", rx);
}
