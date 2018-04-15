#include "stm32f4xx_hal.h"
#include "gpio_a2_exit.h"


void gpio_a2_exit_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;
	
	PA2_EXIT_CLK_ENABLE();
	
	GPIO_InitStruct.Pin = PA2_EXIT_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING; 
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
	
	HAL_GPIO_Init(PA2_EXIT_PORT, &GPIO_InitStruct);
	
	HAL_NVIC_SetPriority(PA2_INT_EXTI, 0x0F, 0x00);
	HAL_NVIC_EnableIRQ(PA2_INT_EXTI);
}

void PA2_INT_EXTIHandler(void)
{
  HAL_GPIO_EXTI_IRQHandler(PA2_EXIT_PIN);
}
