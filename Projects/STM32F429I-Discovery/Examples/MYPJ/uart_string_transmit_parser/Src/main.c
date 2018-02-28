#include "main.h"

extern UART_HandleTypeDef UartHandle3;

int main(void)
{
	system_initialization();
	uart_printf_init();
	uart3_init();

	transmit_pzem_voltage(&UartHandle3);
	transmit_at_uart(&UartHandle3);
}
