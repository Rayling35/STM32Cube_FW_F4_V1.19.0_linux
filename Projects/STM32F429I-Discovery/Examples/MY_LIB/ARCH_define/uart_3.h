#ifndef _UART_3_H_
#define _UART_3_H_

void _UART3_MspInit(void);
void _UART3_MspDeInit(void);

#ifdef UART3_IT
void USART3_IRQHandler(void);
#endif

#endif
