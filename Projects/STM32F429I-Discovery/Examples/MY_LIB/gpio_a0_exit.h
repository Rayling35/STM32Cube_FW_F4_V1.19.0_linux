#ifndef __GPIO_A0_EXIT_H
#define __GPIO_A0_EXIT_H


#define PA0_EXIT_CLK_ENABLE()           __HAL_RCC_GPIOA_CLK_ENABLE()
#define PA0_EXIT_CLK_DISABLE()          __HAL_RCC_GPIOA_CLK_DISABLE()

#define PA0_EXIT_PIN                    GPIO_PIN_0
#define PA0_EXIT_PORT                   GPIOA

#define PA0_INT_EXTI                    EXTI0_IRQn
#define PA0_INT_EXTIHandler             EXTI0_IRQHandler


void gpio_a0_exit_init(void);


#endif
