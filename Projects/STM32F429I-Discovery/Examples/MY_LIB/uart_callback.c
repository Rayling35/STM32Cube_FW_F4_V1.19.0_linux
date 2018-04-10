#include "uart_callback.h"
#include "api_define.h"


#ifdef UART3_IT
	__IO FlagStatus uart3_rx_callbake_flag = RESET;
	#include "uart3.h"
	#ifdef UART3_DMA
		#ifdef U3_DMA_CALLBACK_PARSER
			#include "uart_dma_callback_parser.h"
		#endif
	#endif
	
	#ifdef U3_IT_CALLBACK_PARSER
		#include "uart_it_callback_parser.h"
	#endif
#endif

#ifdef UART6_IT
	__IO FlagStatus uart6_rx_callbake_flag = RESET;
	#include "uart6.h"
	#ifdef UART6_DMA
		#ifdef U6_DMA_CALLBACK_PARSER
			#include "uart_dma_callback_parser.h"
		#endif
	#endif
	
	#ifdef U6_IT_CALLBACK_PARSER
		#include "uart_it_callback_parser.h"
	#endif
#endif

#ifdef UART7_IT
	__IO FlagStatus uart7_rx_callbake_flag = RESET;
	#include "uart7.h"
	#ifdef UART7_DMA
		#ifdef U7_DMA_CALLBACK_PARSER
			#include "uart_dma_callback_parser.h"
		#endif
	#endif
	
	#ifdef U7_IT_CALLBACK_PARSER
		#include "uart_it_callback_parser.h"
	#endif
#endif

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *UartHandle)
{
	#ifdef UART3_IT
	struct uart_api *uart3 = (struct uart_api *)uart3_binding();
	if(UartHandle == uart3->handle) {
	}
	#endif

	#ifdef UART6_IT
	struct uart_api *uart6 = (struct uart_api *)uart6_binding();
	if(UartHandle == uart6->handle) {
	}
	#endif

	#ifdef UART7_IT
	struct uart_api *uart7 = (struct uart_api *)uart7_binding();
	if(UartHandle == uart7->handle) {
	}
	#endif
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle)
{
	#ifdef UART3_IT
	struct uart_api *uart3 = (struct uart_api *)uart3_binding();
	if(UartHandle == uart3->handle) {
		uart3_rx_callbake_flag = RESET;
		#ifdef U3_IT_CALLBACK_PARSER
		SEL_UART3_IT_CALLBACK_PARSER(uart3);
		#endif
		#ifdef U3_DMA_CALLBACK_PARSER
		SEL_UART3_DMA_CALLBACK_PARSER(uart3);
		#endif
	}
	#endif

	#ifdef UART6_IT
	struct uart_api *uart6 = (struct uart_api *)uart6_binding();
	if(UartHandle == uart6->handle) {
		uart6_rx_callbake_flag = RESET;
		#ifdef U6_IT_CALLBACK_PARSER
		SEL_UART6_IT_CALLBACK_PARSER(uart6);
		#endif
		#ifdef U6_DMA_CALLBACK_PARSER
		SEL_UART6_DMA_CALLBACK_PARSER(uart6);
		#endif
	}
	#endif

	#ifdef UART7_IT
	struct uart_api *uart7 = (struct uart_api *)uart7_binding();
	if(UartHandle == uart7->handle) {
		uart7_rx_callbake_flag = RESET;
		#ifdef U7_IT_CALLBACK_PARSER
		SEL_UART7_IT_CALLBACK_PARSER(uart7);
		#endif
		#ifdef U7_DMA_CALLBACK_PARSER
		SEL_UART7_DMA_CALLBACK_PARSER(uart7);
		#endif
	}
	#endif
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *UartHandle)
{
	#ifdef UART3_IT
	struct uart_api *uart3 = (struct uart_api *)uart3_binding();
	if(UartHandle == uart3->handle) {
	}
	#endif

	#ifdef UART6_IT
	struct uart_api *uart6 = (struct uart_api *)uart6_binding();
	if(UartHandle == uart6->handle) {
	}
	#endif

	#ifdef UART7_IT
	struct uart_api *uart7 = (struct uart_api *)uart7_binding();
	if(UartHandle == uart7->handle) {
	}
	#endif
}

// DMA only
void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
	#ifdef UART3_DMA
	_DMA_UART3_MspInit();
	#endif
	
	#ifdef UART6_DMA
	_DMA_UART6_MspInit();
	#endif
	
	#ifdef UART7_DMA
	_DMA_UART7_MspInit();
	#endif
}

void HAL_UART_MspDeInit(UART_HandleTypeDef *huart)
{
	#ifdef UART3_DMA
	_DMA_UART3_MspDeInit();
	#endif
	
	#ifdef UART6_DMA
	_DMA_UART6_MspDeInit();
	#endif
	
	#ifdef UART7_DMA
	_DMA_UART7_MspDeInit();
	#endif
}
