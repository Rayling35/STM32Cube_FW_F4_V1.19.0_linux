#include "stm32f4xx_hal.h"
#include "gpio_a0_exit.h"


void gpio_a0_exit_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;
	
	PA0_EXIT_CLK_ENABLE();
	
	GPIO_InitStruct.Pin   = PA0_EXIT_PIN;
	GPIO_InitStruct.Mode  = GPIO_MODE_IT_RISING;
	GPIO_InitStruct.Pull  = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
	
	HAL_GPIO_Init(PA0_EXIT_PORT, &GPIO_InitStruct);
	
	HAL_NVIC_SetPriority(PA0_INT_EXTI, 0x02, 0x00);
	HAL_NVIC_EnableIRQ(PA0_INT_EXTI);
}

void PA0_INT_EXTIHandler(void)
{
	HAL_GPIO_EXTI_IRQHandler(PA0_EXIT_PIN);
}
