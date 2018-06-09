/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include "api_define.h"
#include "uart_common_api.h"
#include "uart_driver.h"


static int transmit_data(struct device *dev, uint8_t *tx_data, uint16_t length)
{
	struct uart_data *d_data           = dev->data;
	const struct uart_config *d_config = dev->config;
	struct uart_api *uart_hal          = d_data->uart_hal;
	int status;
	
	switch (d_config->mode) {
		case POLLING:
			status = uart_hal->transmit(tx_data, length, d_config->tx_timeout);
			break;
		case IT:
			status = uart_hal->transmit_it(tx_data, length);
			break;
		case DMA:
			status = uart_hal->transmit_dma(tx_data, length);
			break;
		default:
			return -1;
	}
	return status;
}

static int receive_data(struct device *dev, uint8_t *rx_data, uint16_t length)
{
	struct uart_data *d_data           = dev->data;
	const struct uart_config *d_config = dev->config;
	struct uart_api *uart_hal          = d_data->uart_hal;
	int status;
	
	switch (d_config->mode) {
		case POLLING:
			status = uart_hal->receive(rx_data, length, d_config->rx_timeout);
			break;
		case IT:
			status = uart_hal->receive_it(rx_data, length);
			break;
		case DMA:
			status = uart_hal->receive_dma(rx_data, length);
			break;
		default:
			return -1;
	}
	return status;
}

static const struct uart_common_api uart_common_api = {
	.transmit = transmit_data,
	.receive  = receive_data,
};


#ifdef UART3_DEV
#include "uart3.h"
static struct uart_data uart3_data;

static const struct uart_config uart3_config = {
	.tx_timeout = 100,
	.rx_timeout = 100,
	.mode = DMA,
};

static int uart3_dev_init(struct device *dev)
{
	struct uart_data *d_data = dev->data;
	
	d_data->uart_hal = uart3_binding();
	d_data->uart_hal->init();
	printf("UART3 device init\r\n");
	
	return 0;
}

struct device uart_3 = {
	.api    = &uart_common_api,
	.data   = &uart3_data,
	.config = &uart3_config,
	.init   = uart3_dev_init,
};

struct device* uart3_device_binding(void)
{
	return &uart_3;
}

#ifdef UART3_IT
__weak void uart3_tx_callback_handel(struct device *dev)
{
}
__weak void uart3_rx_callback_handel(struct device *dev)
{
}
__weak void uart3_error_callback_handel(struct device *dev)
{
}
#endif
#endif

#ifdef UART6_DEV
#include "uart6.h"
static struct uart_data uart6_data;

static const struct uart_config uart6_config = {
	.tx_timeout = 100,
	.rx_timeout = 100,
	.mode = POLLING,
};

static int uart6_dev_init(struct device *dev)
{
	struct uart_data *d_data = dev->data;
	
	d_data->uart_hal = uart6_binding();
	d_data->uart_hal->init();
	printf("UART6 device init\r\n");
	
	return 0;
}

struct device uart_6 = {
	.api    = &uart_common_api,
	.data   = &uart6_data,
	.config = &uart6_config,
	.init   = uart6_dev_init,
};

struct device* uart6_device_binding(void)
{
	return &uart_6;
}

#ifdef UART6_IT
__weak void uart6_tx_callback_handel(struct device *dev)
{
}
__weak void uart6_rx_callback_handel(struct device *dev)
{
}
__weak void uart6_error_callback_handel(struct device *dev)
{
}
#endif
#endif

#ifdef UART7_DEV
#include "uart7.h"
static struct uart_data uart7_data;

static const struct uart_config uart7_config = {
	.tx_timeout = 100,
	.rx_timeout = 100,
	.mode = POLLING,
};

static int uart7_dev_init(struct device *dev)
{
	struct uart_data *d_data = dev->data;
	
	d_data->uart_hal = uart7_binding();
	d_data->uart_hal->init();
	printf("UART7 device init\r\n");
	
	return 0;
}

struct device uart_7 = {
	.api    = &uart_common_api,
	.data   = &uart7_data,
	.config = &uart7_config,
	.init   = uart7_dev_init,
};

struct device* uart7_device_binding(void)
{
	return &uart_7;
}

#ifdef UART7_IT
__weak void uart7_tx_callback_handel(struct device *dev)
{
}
__weak void uart7_rx_callback_handel(struct device *dev)
{
}
__weak void uart7_error_callback_handel(struct device *dev)
{
}
#endif
#endif


void HAL_UART_TxCpltCallback(UART_HandleTypeDef *UartHandle)
{
	#ifdef UART3_IT
	if(UartHandle->Instance == USART3) {
		uart3_tx_callback_handel(&uart_3);
	}
	#endif
	
	#ifdef UART6_IT
	if(UartHandle->Instance == USART6) {
		uart6_tx_callback_handel(&uart_6);
	}
	#endif
	
	#ifdef UART7_IT
	if(UartHandle->Instance == UART7) {
		uart7_tx_callback_handel(&uart_7);
	}
	#endif
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle)
{
	#ifdef UART3_IT
	if(UartHandle->Instance == USART3) {
		uart3_rx_callback_handel(&uart_3);
	}
	#endif
	
	#ifdef UART6_IT
	if(UartHandle->Instance == USART6) {
		uart6_rx_callback_handel(&uart_6);
	}
	#endif
	
	#ifdef UART7_IT
	if(UartHandle->Instance == UART7) {
		uart7_rx_callback_handel(&uart_7);
	}
	#endif
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *UartHandle)
{
	#ifdef UART3_IT
	if(UartHandle->Instance == USART3) {
		uart3_error_callback_handel(&uart_3);
	}
	#endif
	
	#ifdef UART6_IT
	if(UartHandle->Instance == USART6) {
		uart6_error_callback_handel(&uart_6);
	}
	#endif
	
	#ifdef UART7_IT
	if(UartHandle->Instance == UART7) {
		uart7_error_callback_handel(&uart_7);
	}
	#endif
}
