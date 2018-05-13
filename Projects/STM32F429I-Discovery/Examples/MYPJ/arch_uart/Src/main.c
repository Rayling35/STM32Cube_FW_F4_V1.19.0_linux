#include "system_initialization.h"
#include "uart_printf.h"
#include "main.h"

#include "device.h"
#include "uart_driver.h"
#include "uart_common_api.h"


int main(void)
{
	system_initialization();
	uart_printf_init();
	struct device *dev_uart = (struct device *)uart3_binding();
	dev_uart->init(dev_uart);	

	uint8_t tx[] = "uart3_txxx";
	uint8_t rx[10];
	
	uart_write(dev_uart, tx, 10);
	HAL_Delay(200);
	uart_read(dev_uart, rx, 10);
	printf("rx=%s\r\n", rx);
}
