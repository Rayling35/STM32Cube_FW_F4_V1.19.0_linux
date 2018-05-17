#include "system_initialization.h"
#include "uart_printf.h"
#include "device.h"
#include "uart_driver.h"
#include "uart_common_api.h"
#include "main.h"


uint8_t Buffer[1];
uint8_t ok[] = "ok";

int main(void)
{
	system_initialization();
	uart_printf_init();
	
	struct device *uart3 = uart3_device_binding();
	struct device *uart6 = uart6_device_binding();
	struct device *uart7 = uart7_device_binding();
	uart_init(uart3);
	uart_init(uart6);
	uart_init(uart7);
	printf("UART device init\r\n");
	
	while(1) {
		uart_receive(uart3, Buffer, 1);
		uart_receive(uart6, Buffer, 1);
		uart_receive(uart7, Buffer, 1);
		if(Buffer[0] == 0x66) {
			printf("Hi fff\r\n");
			uart_transmit(uart3, ok, 2);
			uart_transmit(uart6, ok, 2);
			uart_transmit(uart7, ok, 2);
		}
  }
}
