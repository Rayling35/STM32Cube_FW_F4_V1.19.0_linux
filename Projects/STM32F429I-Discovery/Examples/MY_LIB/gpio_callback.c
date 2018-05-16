#include "gpio_callback.h"
#include "api_define.h"


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	#ifdef A0_EXIT
	#include "gpio_g13.h"
	if(GPIO_Pin == GPIO_PIN_0) {
		struct gpio_api *gpio_g13 = gpio_g13_binding();
		gpio_g13->toggle_write();
	}
	#endif
}
