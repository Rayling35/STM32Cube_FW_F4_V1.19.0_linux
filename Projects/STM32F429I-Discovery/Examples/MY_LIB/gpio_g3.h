#ifndef __GPIO_G3_H
#define __GPIO_G3_H


#define PG3_CLK_ENABLE()          __HAL_RCC_GPIOG_CLK_ENABLE()
#define PG3_CLK_DISABLE()         __HAL_RCC_GPIOG_CLK_DISABLE()

#define PG3_PIN                   GPIO_PIN_3
#define PG3_PORT                  GPIOG


struct gpio_api* gpio_g3_binding(void);

#endif
