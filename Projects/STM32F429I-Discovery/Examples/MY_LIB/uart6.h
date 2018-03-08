#ifndef __UART6_H
#define __UART6_H

#include "stm32f4xx_hal.h"

#define USART6_CLK_ENABLE()              __HAL_RCC_USART6_CLK_ENABLE()
#define USART6_RX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOC_CLK_ENABLE()
#define USART6_TX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOC_CLK_ENABLE() 

#define USART6_FORCE_RESET()             __HAL_RCC_USART6_FORCE_RESET()
#define USART6_RELEASE_RESET()           __HAL_RCC_USART6_RELEASE_RESET()

#define USART6_TX_PIN                    GPIO_PIN_6
#define USART6_TX_GPIO_PORT              GPIOC  
#define USART6_TX_AF                     GPIO_AF8_USART6

#define USART6_RX_PIN                    GPIO_PIN_7
#define USART6_RX_GPIO_PORT              GPIOC 
#define USART6_RX_AF                     GPIO_AF8_USART6

#ifdef UART6_IT
#define USART6_IRQn                      USART6_IRQn
#endif

#ifdef UART6_IT
void USART6_IRQHandler(void);
#endif
void uart6_init(void);

#endif
