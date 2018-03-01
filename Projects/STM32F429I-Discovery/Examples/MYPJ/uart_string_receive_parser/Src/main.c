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
	printf("START = %02X\n", *version->start);
	printf("CMD = %c\n", *version->cmd);
	printf("VER1 = %.5s\n", version->ver1);
	printf("ID = %.26s\n", version->id);
	printf("VER2 = %.3s\n", version->ver2);
	printf("REGION = %.10s\n", version->region);
	printf("END = %02X %02X\n", *version->end, *(version->end+1));
}
