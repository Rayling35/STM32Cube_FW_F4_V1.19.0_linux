#include "main.h"

void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
	_UARTxPrintf_MspInit();
	_UART3_MspInit();
}

void HAL_UART_MspDeInit(UART_HandleTypeDef *huart)
{
	_UARTxPrintf_MspDeInit();
	_UART3_MspDeInit();
}
