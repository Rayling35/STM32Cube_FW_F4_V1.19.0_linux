#ifndef __API_LINK_H
#define __API_LINK_H

#include "stm32f4xx_hal.h"


#ifdef HAL_UART_MODULE_ENABLED
struct uart_api {
	UART_HandleTypeDef *handle;
	void (*init)(void);
	int (*transmit)(uint8_t *data, uint16_t length, uint32_t timeout);
	int (*receive)(uint8_t *data, uint16_t length, uint32_t timeout);
	int (*transmit_it)(uint8_t *data, uint16_t length);
	int (*receive_it)(uint8_t *data, uint16_t length);
	int (*transmit_dma)(uint8_t *data, uint16_t length);
	int (*receive_dma)(uint8_t *data, uint16_t length);
};
#endif

#ifdef HAL_I2C_MODULE_ENABLED
struct i2c_api {
	I2C_HandleTypeDef *handle;
	void (*init)(void);
	int (*transmit)(uint8_t *data, uint16_t length, uint32_t timeout);
	int (*receive)(uint8_t *data, uint16_t length, uint32_t timeout);
	int (*transmit_it)(uint8_t *data, uint16_t length);
	int (*receive_it)(uint8_t *data, uint16_t length);
	int (*transmit_dma)(uint8_t *data, uint16_t length);
	int (*receive_dma)(uint8_t *data, uint16_t length);
};
#endif

#ifdef HAL_SPI_MODULE_ENABLED
struct spi_api {
	SPI_HandleTypeDef *handle;
	void (*init)(void);
	int (*transmit)(uint8_t *data, uint16_t length, uint32_t timeout);
	int (*receive)(uint8_t *data, uint16_t length, uint32_t timeout);
	int (*transmit_it)(uint8_t *data, uint16_t length);
	int (*receive_it)(uint8_t *data, uint16_t length);
	int (*transmit_dma)(uint8_t *data, uint16_t length);
	int (*receive_dma)(uint8_t *data, uint16_t length);
};
#endif


#endif
