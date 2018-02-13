#include "stm32f4xx_it.h"

extern UART_HandleTypeDef UartHandle3;

void NMI_Handler(void)
{
}

void HardFault_Handler(void)
{
  while(1) {
  }
}

void MemManage_Handler(void)
{
  while(1) {
  }
}

void BusFault_Handler(void)
{
  while(1) {
  }
}

void UsageFault_Handler(void)
{
  while(1) {
  }
}

void SVC_Handler(void)
{
}

void DebugMon_Handler(void)
{
}

void PendSV_Handler(void)
{
}

void SysTick_Handler(void)
{
  HAL_IncTick();
}

void EXTI0_IRQHandler(void)
{
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
}

void USART3_IRQHandler(void)
{
  HAL_UART_IRQHandler(&UartHandle3);
}

/*void PPP_IRQHandler(void)
{
}*/

