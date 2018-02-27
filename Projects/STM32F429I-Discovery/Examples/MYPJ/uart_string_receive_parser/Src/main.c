#include "main.h"

extern UART_HandleTypeDef UartHandle3;

int main(void)
{
	system_initialization();
	uart_printf_init();
	uart3_init();

	uint8_t buffer[100];
	struct receive_table_a *a;
	struct receive_table_version *version;
	
	receive_cmd_a(&UartHandle3, buffer, 100);
	a = (struct receive_table_a*)buffer;
	printf("a->start: %s\n", a->start);
	int i = atoi(a->end);
	float f = atof(a->data1);

	receive_cmd_version(&UartHandle3, buffer, 100);
	version = (struct receive_table_version*)buffer;
	printf("version->start: %x\n", *version->start);
	printf("version->cmd: %x\n", *version->cmd);
	printf("version->ver1: %s\n", version->ver1);
}
