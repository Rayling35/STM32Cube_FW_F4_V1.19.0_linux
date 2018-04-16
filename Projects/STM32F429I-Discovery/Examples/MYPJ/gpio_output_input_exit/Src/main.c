#include "system_initialization.h"
#include "uart_printf.h"
#include "main.h"

#include "gpio_g13_output.h"
#ifdef A0_EXIT
	#include "gpio_a0_exit.h"
#else
	#include "gpio_a0_input.h"
#endif


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
		if(PA0_GetState()) {
			PG13_OUTPUT_HIGH();
			printf("OUTPUT_HIGH %d\n\r", (uint16_t)PA0_GetState());
			HAL_Delay(100);
		}else {
			PG13_OUTPUT_LOW();
			printf("OUTPUT_LOW %d\n\r", (uint16_t)PA0_GetState());
			HAL_Delay(100);
		}
	}
	#endif
}
