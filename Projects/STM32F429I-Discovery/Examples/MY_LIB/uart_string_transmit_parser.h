#ifndef __UART_STRING_TRANSMIT_PARSER_H
#define __UART_STRING_TRANSMIT_PARSER_H

#include "stm32f4xx_hal.h"
#include <string.h>

uint16_t transmit_pzem_voltage(UART_HandleTypeDef *huart);
uint16_t transmit_at_uart(UART_HandleTypeDef *huart);

#endif

















































