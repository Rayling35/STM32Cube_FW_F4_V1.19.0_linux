#include "main.h"

extern UART_HandleTypeDef UartHandle3;

int main(void)
{
	system_initialization();
	uart_printf_init();
	uart3_init();

	uint8_t rx_buffer[50];
	
	struct receive_table_a *a;
	a = (struct receive_table_a*)rx_buffer;
	receive_cmd_a(&UartHandle3, rx_buffer, 50);
	a_parser(rx_buffer);
	
	printf("START = %s\r\n", a->start);

/*---------------------------------------------------------*/
	struct receive_table_version *version;
	version = (struct receive_table_version*)rx_buffer;
	receive_cmd_version(&UartHandle3, rx_buffer, 50);
	version_parser(rx_buffer);
	
	char region[5];
	int re;
	sprintf(region, "%.5s\r\n", version->region);
	re = strtol(region, NULL, 16);
	printf("region %d\r\n", re);
}
