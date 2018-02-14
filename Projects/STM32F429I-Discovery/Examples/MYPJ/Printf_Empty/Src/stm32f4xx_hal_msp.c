#include "main.h"

void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
	_UARTxPrintf_MspInit();
}

void HAL_UART_MspDeInit(UART_HandleTypeDef *huart)
{
	_UARTxPrintf_MspDeInit();
}

