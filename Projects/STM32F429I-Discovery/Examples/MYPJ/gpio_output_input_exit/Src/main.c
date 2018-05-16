#include "system_initialization.h"
#include "uart_printf.h"
#include "main.h"

#include "api_define.h"
#include "gpio_a0.h"
#include "gpio_g13.h"


int main(void)
{
	system_initialization();
	uart_printf_init();
	
	struct gpio_api *gpio_a0  = gpio_a0_binding();
	struct gpio_api *gpio_g13 = gpio_g13_binding();
	
	gpio_g13->output_init();
#ifdef A0_EXIT
	gpio_a0->exit_init();
	while(1) {
	}
#else
	gpio_a0->input_init();
	while(1) {
		if(gpio_a0->read()) {
			gpio_g13->write(1);
			printf("PA0 STATE %d\n\r", gpio_a0->read());
			HAL_Delay(100);
		}else {
			gpio_g13->write(0);
			printf("PA0 STATE %d\n\r", gpio_a0->read());
			HAL_Delay(100);
		}
	}
#endif
}
