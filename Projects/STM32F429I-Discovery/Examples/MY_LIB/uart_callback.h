#ifndef __UART_CALLBACK_H
#define __UART_CALLBACK_H

#include "stm32f4xx_hal.h"

#ifdef UART3_IT
extern __IO FlagStatus uart3_rx_callbake_flag;
#endif

#ifdef UART6_IT
extern __IO FlagStatus uart6_rx_callbake_flag;
#endif

#ifdef UART7_IT
extern __IO FlagStatus uart7_rx_callbake_flag;
#endif


#endif
