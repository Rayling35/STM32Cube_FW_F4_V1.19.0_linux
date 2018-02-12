#include "uart_printf.h"

UART_HandleTypeDef UartHandlePrintf;

#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif

PUTCHAR_PROTOTYPE
{
  HAL_UART_Transmit(&UartHandlePrintf, (uint8_t *)&ch, 1, 0xFFFF);
  return ch;
}

void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{  
  GPIO_InitTypeDef  GPIO_InitStruct;
  
  /* Enable GPIO TX/RX clock */
  USARTxPrintf_TX_GPIO_CLK_ENABLE();
  USARTxPrintf_RX_GPIO_CLK_ENABLE();

  /* Enable UART clock */
  USARTxPrintf_CLK_ENABLE(); 
  
  /* UART TX GPIO pin configuration  */
  GPIO_InitStruct.Pin       = USARTxPrintf_TX_PIN;
  GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull      = GPIO_NOPULL;
  GPIO_InitStruct.Speed     = GPIO_SPEED_FAST;
  GPIO_InitStruct.Alternate = USARTxPrintf_TX_AF;
  HAL_GPIO_Init(USARTxPrintf_TX_GPIO_PORT, &GPIO_InitStruct);
    
  /* UART RX GPIO pin configuration  */
  GPIO_InitStruct.Pin = USARTxPrintf_RX_PIN;
  GPIO_InitStruct.Alternate = USARTxPrintf_RX_AF;
  HAL_GPIO_Init(USARTxPrintf_RX_GPIO_PORT, &GPIO_InitStruct);
}

void HAL_UART_MspDeInit(UART_HandleTypeDef *huart)
{
  USARTxPrintf_FORCE_RESET();
  USARTxPrintf_RELEASE_RESET();

  /* Configure UART Tx as alternate function */
  HAL_GPIO_DeInit(USARTxPrintf_TX_GPIO_PORT, USARTxPrintf_TX_PIN);
  /* Configure UART Rx as alternate function */
  HAL_GPIO_DeInit(USARTxPrintf_RX_GPIO_PORT, USARTxPrintf_RX_PIN);
}


void uart_printf_init(void)
{
  UartHandlePrintf.Instance          = USARTxPrintf;
  UartHandlePrintf.Init.BaudRate     = 115200;
  UartHandlePrintf.Init.WordLength   = UART_WORDLENGTH_8B;
  UartHandlePrintf.Init.StopBits     = UART_STOPBITS_1;
  UartHandlePrintf.Init.Parity       = UART_PARITY_NONE;
  UartHandlePrintf.Init.HwFlowCtl    = UART_HWCONTROL_NONE;
  UartHandlePrintf.Init.Mode         = UART_MODE_TX_RX;
  UartHandlePrintf.Init.OverSampling = UART_OVERSAMPLING_16;
    
  HAL_UART_Init(&UartHandlePrintf);
  printf("** UART Printf() init OK ** \n\r");

}

