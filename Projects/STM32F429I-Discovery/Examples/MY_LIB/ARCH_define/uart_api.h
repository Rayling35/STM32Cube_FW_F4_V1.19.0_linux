#ifndef _UART_API_H_
#define _UART_API_H_

#include <dev.h>

               /*-----------API--------------*/
typedef int (*uart_api_1)(struct device *dev, uint8_t *rxBuffer);
typedef int (*uart_api_2)(struct device *dev, uint8_t *txBuffer);

struct uart_api {
	uart_api_1 read;
	uart_api_2 write;
};


               /*-----------APP--------------*/
static inline int uart_read(struct device *dev, uint8_t *rxBuffer)
{
	const struct uart_api *uart_api = dev->api;
	return uart_api->read(dev, rxBuffer);
}

static inline int uart_write(struct device *dev, uint8_t *txBuffer)
{
	const struct uart_api *uart_api = dev->api;
	return uart_api->write(dev, txBuffer);
}

#endif
