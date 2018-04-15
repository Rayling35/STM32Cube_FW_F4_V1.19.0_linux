#include "stm32f4xx_hal.h"
#include "gpio_a2_output.h"


void gpio_a2_output_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;
	
	PA2_OUTPUT_CLK_ENABLE();
	
	GPIO_InitStruct.Pin = PA2_OUTPUT_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
	
	HAL_GPIO_Init(PA2_OUTPUT_PORT, &GPIO_InitStruct);
}
