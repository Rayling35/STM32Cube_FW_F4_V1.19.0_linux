#include "gpio_g13.h"
#include "api_define.h"


#ifdef G13_OUTPUT
static void gpio_g13_output_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	PG13_CLK_ENABLE();
	
	GPIO_InitStruct.Pin   = PG13_PIN;
	GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull  = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
	
	HAL_GPIO_Init(PG13_PORT, &GPIO_InitStruct);
}
#endif

#ifdef G13_INPUT
static void gpio_g13_input_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;
	
	PG13_CLK_ENABLE();
	
	GPIO_InitStruct.Pin   = PG13_PIN;
	GPIO_InitStruct.Mode  = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull  = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
	
	HAL_GPIO_Init(PG13_PORT, &GPIO_InitStruct);
}
#endif

#ifdef G13_EXIT
static void gpio_g13_exit_init(void)
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

static void gpio_g13_init(void)
{
	#ifdef G13_OUTPUT
	gpio_g13_output_init();
	#endif
	#ifdef G13_INPUT
	gpio_g13_input_init();
	#endif
	#ifdef G13_EXIT
	gpio_g13_exit_init();
	#endif
	printf("GPIO_G13 HAL init\r\n");
}

static int gpio_g13_read(void)
{
	return HAL_GPIO_ReadPin(PG13_PORT, PG13_PIN);
}

static void gpio_g13_write(uint16_t state)
{
	if(state == 0) {
		HAL_GPIO_WritePin(PG13_PORT, PG13_PIN, GPIO_PIN_RESET);
	}
	if(state == 1) {
		HAL_GPIO_WritePin(PG13_PORT, PG13_PIN, GPIO_PIN_SET);
	}
}

static void gpio_g13_toggle_write(void)
{
	HAL_GPIO_TogglePin(PG13_PORT, PG13_PIN);
}

static int gpio_g13_lock(void)
{
	return HAL_GPIO_LockPin(PG13_PORT, PG13_PIN);
}

static struct gpio_api gpio_g13_api = {
	.init         = gpio_g13_init,
	.read         = gpio_g13_read,
	.write        = gpio_g13_write,
	.toggle_write = gpio_g13_toggle_write,
	.lock         = gpio_g13_lock,
};

struct gpio_api* gpio_g13_binding(void)
{
	return &gpio_g13_api;
}
