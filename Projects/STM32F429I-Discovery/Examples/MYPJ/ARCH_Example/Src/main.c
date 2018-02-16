#include <dev.h>
#include <io.h>
#include "main.h"

extern struct device real_io_0;

int main(void)
{
	system_initialization();
	uart_printf_init();
/*----------------------------*/
	
	struct device *ptr_real_io_0 = &real_io_0;

	printf("The init => %d\n", ptr_real_io_0->init(ptr_real_io_0));
	printf("Ues APP => %d\n", io_print(ptr_real_io_0, 4));
	
	const struct io_api *ptr_realio0_api = ptr_real_io_0->api;
	printf("Use API => %d\n", ptr_realio0_api->print(ptr_real_io_0, 4));
}
