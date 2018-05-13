#ifndef __UART_COMMON_API_H
#define __UART_COMMON_API_H

#include "device.h"


               /*-----------API--------------*/
typedef int (*uart_api_1)(struct device *dev, uint8_t *rxBuffer, uint16_t longth, uint16_t timeout);
typedef int (*uart_api_2)(struct device *dev, uint8_t *txBuffer, uint16_t longth, uint16_t timeout);

struct uart_common_api {
	uart_api_1 read;
	uart_api_2 write;
};


               /*-----------APP--------------*/
static inline int uart_read(struct device *dev, uint8_t *rxBuffer, uint16_t length)
{
	const struct uart_common_api *uart_api = dev->api;
	return uart_api->read(dev, rxBuffer, length, 100);
}

static inline int uart_write(struct device *dev, uint8_t *txBuffer, uint16_t length)
{
	const struct uart_common_api *uart_api = dev->api;
	return uart_api->write(dev, txBuffer, length, 100);
}


#endif
