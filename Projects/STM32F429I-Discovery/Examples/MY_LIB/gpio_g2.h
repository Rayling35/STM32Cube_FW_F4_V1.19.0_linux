#ifndef __GPIO_G2_H
#define __GPIO_G2_H


#define PG2_CLK_ENABLE()          __HAL_RCC_GPIOG_CLK_ENABLE()
#define PG2_CLK_DISABLE()         __HAL_RCC_GPIOG_CLK_DISABLE()

#define PG2_PIN                   GPIO_PIN_2
#define PG2_PORT                  GPIOG


struct gpio_api* gpio_g2_binding(void);

#endif
