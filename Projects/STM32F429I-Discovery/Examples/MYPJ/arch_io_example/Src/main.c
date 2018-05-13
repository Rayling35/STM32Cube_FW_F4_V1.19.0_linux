#include "system_initialization.h"
#include "uart_printf.h"
#include "main.h"

#include "device.h"
#include "io_driver.h"
#include "io_common_api.h"


int main(void)
{
	system_initialization();
	uart_printf_init();
	struct device *dev_io = (struct device *)io0_binding();

	printf("The init %d\r\n", dev_io->init(dev_io));
	printf("Use APP %d\r\n", io_func(dev_io, 4));
}
