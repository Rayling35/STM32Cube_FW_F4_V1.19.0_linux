#ifndef __GPIO_C1_H
#define __GPIO_C1_H


#define PC1_CLK_ENABLE()          __HAL_RCC_GPIOC_CLK_ENABLE()
#define PC1_CLK_DISABLE()         __HAL_RCC_GPIOC_CLK_DISABLE()

#define PC1_PIN                   GPIO_PIN_1
#define PC1_PORT                  GPIOC


struct gpio_api* gpio_c1_binding(void);

#endif
