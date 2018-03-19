#ifndef _UART_H_
#define _UART_H_

#include "stm32f4xx_hal.h"


#ifdef UART3_IT
void USART3_IRQHandler(void);
#endif

uint32_t uart3_binding(void);

#endif
