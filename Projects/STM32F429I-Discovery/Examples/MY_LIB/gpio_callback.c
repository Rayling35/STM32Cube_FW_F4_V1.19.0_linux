#include "stm32f4xx_hal.h"
#include "gpio_callback.h"


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	#ifdef A0_EXIT
	#include "gpio_g13.h"
	if(GPIO_Pin == GPIO_PIN_0) {
		PG13_OUTPUT_Toggle();
	}
	#endif
}
