#ifndef __UART_DRIVER_H
#define __UART_DRIVER_H


#ifdef UART3_IT
void USART3_IRQHandler(void);
#endif

uint32_t uart3_binding(void);


#endif
