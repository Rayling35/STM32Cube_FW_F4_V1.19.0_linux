#include "stm32f4xx_hal.h"
#include "gpio_a0.h"


void gpio_a0_output_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	PA0_CLK_ENABLE();
	
	GPIO_InitStruct.Pin   = PA0_PIN;
	GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull  = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
	
	HAL_GPIO_Init(PA0_PORT, &GPIO_InitStruct);
}

void gpio_a0_input_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;
	
	PA0_CLK_ENABLE();
	
	GPIO_InitStruct.Pin   = PA0_PIN;
	GPIO_InitStruct.Mode  = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull  = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
	
	HAL_GPIO_Init(PA0_PORT, &GPIO_InitStruct);
}

#ifdef A0_EXIT
void gpio_a0_exit_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;
	
	PA0_CLK_ENABLE();
	
	GPIO_InitStruct.Pin   = PA0_PIN;
	GPIO_InitStruct.Mode  = GPIO_MODE_IT_RISING;
	GPIO_InitStruct.Pull  = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
	
	HAL_GPIO_Init(PA0_PORT, &GPIO_InitStruct);
	
	HAL_NVIC_SetPriority(EXTI0_IRQn, 2, 0);
	HAL_NVIC_EnableIRQ(EXTI0_IRQn);
}

void EXTI0_IRQHandler(void)
{
	HAL_GPIO_EXTI_IRQHandler(PA0_PIN);
}
#endif
