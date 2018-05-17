#include "api_define.h"
#include "uart_common_api.h"
#include "uart_driver.h"


struct uart_data {
	struct uart_api *uart_hal;
};

struct uart_config {
	uint32_t tx_timeout;
	uint32_t rx_timeout;
};

/*-----------API--------------*/
static int transmit_data(struct device *dev, uint8_t *tx_data, uint16_t length)
{
	struct uart_data *data           = dev->data;
	const struct uart_config *config = dev->config;
	struct uart_api *uart_hal        = data->uart_hal;
	
	return uart_hal->transmit(tx_data, length, config->tx_timeout);
}

static int receive_data(struct device *dev, uint8_t *rx_data, uint16_t length)
{
	struct uart_data *data           = dev->data;
	const struct uart_config *config = dev->config;
	struct uart_api *uart_hal        = data->uart_hal;
	
	return uart_hal->receive(rx_data, length, config->rx_timeout);
}

static const struct uart_common_api uart_common_api = {
	.transmit = transmit_data,
	.receive  = receive_data,
};


#ifdef UART3_DEV
#include "uart3.h"
static struct uart_data uart3_data;
static const struct uart_config uart3_config = {
	.tx_timeout    = 100,
	.rx_timeout    = 100,
};

static int uart3_init(struct device *dev)
{
	struct uart_data *data = dev->data;
	
	data->uart_hal = uart3_binding();
	data->uart_hal->init();
	
	return 0;
}

struct device uart_3 = {
	.api    = &uart_common_api,
	.data   = &uart3_data,
	.config = &uart3_config,
	.init   = uart3_init,
};

struct device* uart3_device_binding(void)
{
	return &uart_3;
}
#endif

#ifdef UART6_DEV
#include "uart6.h"
static struct uart_data uart6_data;
static const struct uart_config uart6_config = {
	.tx_timeout    = 100,
	.rx_timeout    = 100,
};

static int uart6_init(struct device *dev)
{
	struct uart_data *data = dev->data;
	
	data->uart_hal = uart6_binding();
	data->uart_hal->init();
	
	return 0;
}

struct device uart_6 = {
	.api    = &uart_common_api,
	.data   = &uart6_data,
	.config = &uart6_config,
	.init   = uart6_init,
};

struct device* uart6_device_binding(void)
{
	return &uart_6;
}
#endif

#ifdef UART7_DEV
#include "uart7.h"
static struct uart_data uart7_data;
static const struct uart_config uart7_config = {
	.tx_timeout    = 100,
	.rx_timeout    = 100,
};

static int uart7_init(struct device *dev)
{
	struct uart_data *data = dev->data;
	
	data->uart_hal = uart7_binding();
	data->uart_hal->init();
	
	return 0;
}

struct device uart_7 = {
	.api    = &uart_common_api,
	.data   = &uart7_data,
	.config = &uart7_config,
	.init   = uart7_init,
};

struct device* uart7_device_binding(void)
{
	return &uart_7;
}
#endif
