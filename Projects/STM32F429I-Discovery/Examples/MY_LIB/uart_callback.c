#include "uart_callback.h"
#include "api_define.h"
#include "uart3.h"
#include "uart6.h"
#include "uart7.h"


__IO FlagStatus uart3_rx_callbake_flag;
__IO FlagStatus uart6_rx_callbake_flag;
__IO FlagStatus uart7_rx_callbake_flag;

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *UartHandle)
{
	struct uart_api *uart3 = (struct uart_api *)uart3_binding();
	struct uart_api *uart6 = (struct uart_api *)uart6_binding();
	struct uart_api *uart7 = (struct uart_api *)uart7_binding();
	
	if(UartHandle == uart3->handle) {
	}
	if(UartHandle == uart6->handle) {
	}
	if(UartHandle == uart7->handle) {
	}
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle)
{
	struct uart_api *uart3 = (struct uart_api *)uart3_binding();
	struct uart_api *uart6 = (struct uart_api *)uart6_binding();
	struct uart_api *uart7 = (struct uart_api *)uart7_binding();
	
	if(UartHandle == uart3->handle) {
		uart3_rx_callbake_flag = RESET;
	}
	if(UartHandle == uart6->handle) {
		uart6_rx_callbake_flag = RESET;
	}
	if(UartHandle == uart7->handle) {
		uart7_rx_callbake_flag = RESET;
	}
}

 void HAL_UART_ErrorCallback(UART_HandleTypeDef *UartHandle)
{
	struct uart_api *uart3 = (struct uart_api *)uart3_binding();
	struct uart_api *uart6 = (struct uart_api *)uart6_binding();
	struct uart_api *uart7 = (struct uart_api *)uart7_binding();
	
	if(UartHandle == uart3->handle) {
	}
	if(UartHandle == uart6->handle) {
	}
	if(UartHandle == uart7->handle) {
	}	
}
