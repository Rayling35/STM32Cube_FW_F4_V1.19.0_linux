#ifndef __GPIO_A2_INPUT_H
#define __GPIO_A2_INPUT_H


#define PA2_INPUT_CLK_ENABLE()         __HAL_RCC_GPIOA_CLK_ENABLE()
#define PA2_INPUT_CLK_DISABLE()        __HAL_RCC_GPIOA_CLK_DISABLE()

#define PA2_INPUT_PIN                  GPIO_PIN_2
#define PA2_INPUT_PORT                 GPIOA


void gpio_a2_input_init(void);


#endif
