#ifndef __GPIO_A5_H
#define __GPIO_A5_H


#define PA5_CLK_ENABLE()          __HAL_RCC_GPIOA_CLK_ENABLE()
#define PA5_CLK_DISABLE()         __HAL_RCC_GPIOA_CLK_DISABLE()

#define PA5_PIN                   GPIO_PIN_5
#define PA5_PORT                  GPIOA


struct gpio_api* gpio_a5_binding(void);

#endif
