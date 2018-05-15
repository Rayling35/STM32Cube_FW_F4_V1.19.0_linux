#include "stm32f4xx_hal.h"
#include "gpio_g13.h"


void gpio_g13_output_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	PG13_CLK_ENABLE();
	
	GPIO_InitStruct.Pin   = PG13_PIN;
	GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull  = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
	
	HAL_GPIO_Init(PG13_PORT, &GPIO_InitStruct);
}

void gpio_g13_input_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;
	
	PG13_CLK_ENABLE();
	
	GPIO_InitStruct.Pin   = PG13_PIN;
	GPIO_InitStruct.Mode  = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull  = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
	
	HAL_GPIO_Init(PG13_PORT, &GPIO_InitStruct);
}

#ifdef G13_EXIT
void gpio_g13_exit_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;
	
	PG13_CLK_ENABLE();
	
	GPIO_InitStruct.Pin   = PG13_PIN;
	GPIO_InitStruct.Mode  = GPIO_MODE_IT_RISING;
	GPIO_InitStruct.Pull  = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
	
	HAL_GPIO_Init(PG13_PORT, &GPIO_InitStruct);
	
	HAL_NVIC_SetPriority(EXTI1_IRQn, 2, 0);
	HAL_NVIC_EnableIRQ(EXTI1_IRQn);
}

void EXTI1_IRQHandler(void)
{
	HAL_GPIO_EXTI_IRQHandler(PG13_PIN);
}
#endif
