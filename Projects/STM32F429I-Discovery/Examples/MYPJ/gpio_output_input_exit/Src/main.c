#include "system_initialization.h"
#include "uart_printf.h"
#include "main.h"

#include "gpio_g13.h"
#include "gpio_a0.h"


int main(void)
{
	system_initialization();
	uart_printf_init();
	
	gpio_g13_output_init();
#ifdef A0_EXIT
	gpio_a0_exit_init();
	while(1) {
	}
#else
	gpio_a0_input_init();
	while(1) {
		if(PA0_GET_STATE()) {
			PG13_OUTPUT_HIGH();
			printf("PA0 STATE %d\n\r", PA0_GET_STATE());
			HAL_Delay(100);
		}else {
			PG13_OUTPUT_LOW();
			printf("PA0 STATE %d\n\r", PA0_GET_STATE());
			HAL_Delay(100);
		}
	}
#endif
}
