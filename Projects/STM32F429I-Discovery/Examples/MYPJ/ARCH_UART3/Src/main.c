#include <dev.h>
#include <uart_api.h>
#include "main.h"

extern struct device uart_3;
struct device *uart3 = &uart_3;

uint8_t rx[10];
uint8_t tx[] = "uart3_txxx";

int main(void)
{
	system_initialization();
	//uart_printf_init();
/*----------------------------*/

	uart3->init(uart3);
	uart_read(uart3, rx);
	uart_write(uart3, tx);
}
