#ifndef __API_LINK_H
#define __API_LINK_H

#include "stm32f4xx_hal.h"

struct uart_api {
	UART_HandleTypeDef *handle;
	void (*init)(void);
	int (*transmit)(uint8_t *data, uint16_t length, uint32_t timeout);
	int (*receive)(uint8_t *data, uint16_t length, uint32_t timeout);
	int (*transmit_it)(uint8_t *data, uint16_t length);
	int (*receive_it)(uint8_t *data, uint16_t length);
};

#endif
