#ifndef __GPIO_A0_H
#define __GPIO_A0_H


#define PA0_CLK_ENABLE()          __HAL_RCC_GPIOA_CLK_ENABLE()
#define PA0_CLK_DISABLE()         __HAL_RCC_GPIOA_CLK_DISABLE()

#define PA0_PIN                   GPIO_PIN_0
#define PA0_PORT                  GPIOA


struct gpio_api* gpio_a0_binding(void);

#endif
