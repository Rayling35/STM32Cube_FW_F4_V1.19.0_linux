#ifndef __UART3_H
#define __UART3_H

#include "stm32f4xx_hal.h"

#define USART3_CLK_ENABLE()              __HAL_RCC_USART3_CLK_ENABLE()
#define USART3_RX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOD_CLK_ENABLE()
#define USART3_TX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOD_CLK_ENABLE() 

#define USART3_FORCE_RESET()             __HAL_RCC_USART3_FORCE_RESET()
#define USART3_RELEASE_RESET()           __HAL_RCC_USART3_RELEASE_RESET()

#define USART3_TX_PIN                    GPIO_PIN_8
#define USART3_TX_GPIO_PORT              GPIOD  
#define USART3_TX_AF                     GPIO_AF7_USART3

#define USART3_RX_PIN                    GPIO_PIN_9
#define USART3_RX_GPIO_PORT              GPIOD 
#define USART3_RX_AF                     GPIO_AF7_USART3

#ifdef UART3_IT
#define USART3_IRQn                      USART3_IRQn
#endif

#ifdef UART3_IT
void USART3_IRQHandler(void);
#endif
void uart3_init(void);

#endif
