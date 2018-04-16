#include "stm32f4xx_hal.h"
#include "gpio_callback.h"


#ifdef A0_EXIT
#include "gpio_g13_output.h"
#include "gpio_a0_exit.h"

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == PA0_EXIT_PIN) {
		PG13_OUTPUT_Toggle();
	}
}
#endif
