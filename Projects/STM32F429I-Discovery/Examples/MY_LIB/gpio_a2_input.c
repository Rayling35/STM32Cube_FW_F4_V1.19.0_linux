#include "stm32f4xx_hal.h"
#include "gpio_a2_input.h"


void gpio_a2_input_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;
	
	PA2_INPUT_CLK_ENABLE();
	
	GPIO_InitStruct.Pin = PA2_INPUT_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
	
	HAL_GPIO_Init(PA2_INPUT_PORT, &GPIO_InitStruct);
}
