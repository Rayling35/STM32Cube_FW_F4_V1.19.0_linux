#ifndef __UART7_H
#define __UART7_H

#include "stm32f4xx_hal.h"

#define UART7_CLK_ENABLE()              __HAL_RCC_UART7_CLK_ENABLE()
#define UART7_RX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOF_CLK_ENABLE()
#define UART7_TX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOF_CLK_ENABLE()

#define UART7_FORCE_RESET()             __HAL_RCC_UART7_FORCE_RESET()
#define UART7_RELEASE_RESET()           __HAL_RCC_UART7_RELEASE_RESET()

#define BAUDRATE                        115200

#define UART7_TX_PIN                    GPIO_PIN_7
#define UART7_TX_GPIO_PORT              GPIOF
#define UART7_TX_AF                     GPIO_AF8_UART7

#define UART7_RX_PIN                    GPIO_PIN_6
#define UART7_RX_GPIO_PORT              GPIOF
#define UART7_RX_AF                     GPIO_AF8_UART7

struct uart_api* uart7_binding(void);

#ifdef UART7_IT
void UART7_IRQHandler(void);
#endif


#endif
