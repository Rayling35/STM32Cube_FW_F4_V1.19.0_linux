#include "system_initialization.h"
#include "uart_printf.h"
#include "device.h"
#include "nrf24l01_driver.h"
#include "rf_common_api.h"
#include "main.h"


int main(void)
{
	system_initialization();
	uart_printf_init();
	
	struct device *nrf24l01 = nrf24l01_device_binding();
	rf_init(nrf24l01);
	printf("All device init finish\r\n");
	
	rf_device_test(nrf24l01);
	
	while(1) {
	}
}
