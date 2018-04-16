#include "stm32f4xx_hal.h"
#include "gpio_g13_output.h"


void gpio_g13_output_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	PG13_OUTPUT_CLK_ENABLE();
	
	GPIO_InitStruct.Pin = PG13_OUTPUT_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
	
	HAL_GPIO_Init(PG13_OUTPUT_PORT, &GPIO_InitStruct);
}
