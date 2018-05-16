#ifndef __GPIO_G13_H
#define __GPIO_G13_H


#define PG13_CLK_ENABLE()         __HAL_RCC_GPIOG_CLK_ENABLE()
#define PG13_CLK_DISABLE()        __HAL_RCC_GPIOG_CLK_DISABLE()

#define PG13_PIN                  GPIO_PIN_13
#define PG13_PORT                 GPIOG


struct gpio_api* gpio_g13_binding(void);

#endif
