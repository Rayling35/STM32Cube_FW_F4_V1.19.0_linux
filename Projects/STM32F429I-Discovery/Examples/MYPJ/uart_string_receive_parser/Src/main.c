#include "main.h"

extern UART_HandleTypeDef UartHandle3;

int main(void)
{
	system_initialization();
	uart_printf_init();
	uart3_init();

	uint16_t rx_length = 100;
	uint8_t rx_buffer[rx_length];
	
	struct receive_table_a *a;
	a = (struct receive_table_a*)rx_buffer;
	receive_cmd_a(&UartHandle3, rx_buffer, rx_length);
	printf("a->start: %s\n", a->start);
	int i = atoi(a->end);
	float f = atof(a->data1);

	struct receive_table_version *version;
	version = (struct receive_table_version*)rx_buffer;
	receive_cmd_version(&UartHandle3, rx_buffer, rx_length);
	printf("version->start: %x\n", *version->start);
	printf("version->cmd: %x\n", *version->cmd);
	printf("version->ver1: %s\n", version->ver1);
}
