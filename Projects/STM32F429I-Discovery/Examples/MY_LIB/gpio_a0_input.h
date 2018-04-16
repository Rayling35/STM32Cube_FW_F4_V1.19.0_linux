#ifndef __GPIO_A0_INPUT_H
#define __GPIO_A0_INPUT_H


#define PA0_INPUT_CLK_ENABLE()          __HAL_RCC_GPIOA_CLK_ENABLE()
#define PA0_INPUT_CLK_DISABLE()         __HAL_RCC_GPIOA_CLK_DISABLE()

#define PA0_INPUT_PIN                   GPIO_PIN_0
#define PA0_INPUT_PORT                  GPIOA


#define PA0_GetState()          HAL_GPIO_ReadPin(PA0_INPUT_PORT, PA0_INPUT_PIN)

void gpio_a0_input_init(void);


#endif
