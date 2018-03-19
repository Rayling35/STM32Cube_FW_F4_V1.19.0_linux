#ifndef __UART_STRING_TRANSMIT_PARSER_H
#define __UART_STRING_TRANSMIT_PARSER_H

#include "stm32f4xx_hal.h"
#include "api_define.h"


uint16_t transmit_pzem_voltage(struct uart_api *huart);
uint16_t transmit_at_uart(struct uart_api *huart);

#endif
