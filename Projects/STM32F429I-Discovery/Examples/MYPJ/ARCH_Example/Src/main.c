#include <dev.h>
#include <io_api.h>
#include "main.h"

extern struct device io_0;
struct device *io0 = &io_0;

int main(void)
{
	system_initialization();
	uart_printf_init();
/*----------------------------*/

	printf("The init %d\r\n", io0->init(io0));
	printf("Use APP %d\r\n", io_func(io0, 4));
	
	const struct io_api *io0_api = io0->api;
	printf("Use API %d\r\n\n", io0_api->func(io0, 4));
}
