#ifndef __UART_DRIVER_H
#define __UART_DRIVER_H


enum uart_mode{
	POLLING,
	IT,
	DMA,
};

struct uart_data {
	struct uart_api *uart_hal;
};

struct uart_config {
	uint32_t tx_timeout;
	uint32_t rx_timeout;
	enum uart_mode mode;
};

#ifdef UART3_DEV
struct device* uart3_device_binding(void);
#endif

#ifdef UART6_DEV
struct device* uart6_device_binding(void);
#endif

#ifdef UART7_DEV
struct device* uart7_device_binding(void);
#endif


#endif
