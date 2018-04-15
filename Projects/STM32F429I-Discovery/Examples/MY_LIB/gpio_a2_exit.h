#ifndef __GPIO_A2_EXIT_H
#define __GPIO_A2_EXIT_H


#define PA2_EXIT_CLK_ENABLE()          __HAL_RCC_GPIOA_CLK_ENABLE()
#define PA2_EXIT_CLK_DISABLE()         __HAL_RCC_GPIOA_CLK_DISABLE()

#define PA2_EXIT_PIN                   GPIO_PIN_2
#define PA2_EXIT_PORT                  GPIOA

#define PA2_INT_EXTI                   EXTI0_IRQn
#define PA2_INT_EXTIHandler            EXTI0_IRQHandler


void gpio_a2_exit_init(void);


#endif
