#include "uart_callback.h"
#include "api_define.h"


#ifdef UART3_IT
	#include "uart3.h"
	#ifdef UART3_DMA
		#include "uart3_dma.h"
		#ifdef DMA_CALLBACK_PARSER_U3
			#include "uart_dma_callback_parser.h"
		#endif
	#endif
	#ifdef IT_CALLBACK_PARSER_U3
		#include "uart_it_callback_parser.h"
	#endif
__IO FlagStatus uart3_rx_callbake_flag = RESET;
#endif

#ifdef UART6_IT
	#include "uart6.h"
	#ifdef UART6_DMA
		#include "uart6_dma.h"
		#ifdef DMA_CALLBACK_PARSER_U6
			#include "uart_dma_callback_parser.h"
		#endif
	#endif
	#ifdef IT_CALLBACK_PARSER_U6
		#include "uart_it_callback_parser.h"
	#endif
	__IO FlagStatus uart6_rx_callbake_flag = RESET;
#endif

#ifdef UART7_IT
	#include "uart7.h"
	#ifdef UART7_DMA
		#include "uart7_dma.h"
		#ifdef DMA_CALLBACK_PARSER_U7
			#include "uart_dma_callback_parser.h"
		#endif
	#endif
	#ifdef IT_CALLBACK_PARSER_U7
		#include "uart_it_callback_parser.h"
	#endif
	__IO FlagStatus uart7_rx_callbake_flag = RESET;
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
		#ifdef IT_CALLBACK_PARSER_U3
		uart_it_callback_parser();
		#endif
		#ifdef DMA_CALLBACK_PARSER_U3
		uart_dma1_callback_parser();
		#endif
	}
	#endif

	#ifdef UART6_IT
	struct uart_api *uart6 = (struct uart_api *)uart6_binding();
	if(UartHandle == uart6->handle) {
		uart6_rx_callbake_flag = RESET;
		#ifdef IT_CALLBACK_PARSER_U6
		uart_it_callback_parser();
		#endif
		#ifdef DMA_CALLBACK_PARSER_U6
		uart_dma2_callback_parser();
		#endif
	}
	#endif

	#ifdef UART7_IT
	struct uart_api *uart7 = (struct uart_api *)uart7_binding();
	if(UartHandle == uart7->handle) {
		uart7_rx_callbake_flag = RESET;
		#ifdef IT_CALLBACK_PARSER_U7
		uart_it_callback_parser();
		#endif
		#ifdef DMA_CALLBACK_PARSER_U7
		uart_dma3_callback_parser();
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
