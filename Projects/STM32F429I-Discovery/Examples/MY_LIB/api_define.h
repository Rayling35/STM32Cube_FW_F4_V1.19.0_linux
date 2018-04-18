#ifndef __API_LINK_H
#define __API_LINK_H

#include "stm32f4xx_hal.h"


#ifdef HAL_UART_MODULE_ENABLED
struct uart_api {
	UART_HandleTypeDef *handle;
	void (*init)(void);
	int (*transmit)    (uint8_t *data, uint16_t length, uint32_t timeout);
	int (*receive)     (uint8_t *data, uint16_t length, uint32_t timeout);
	int (*transmit_it) (uint8_t *data, uint16_t length);
	int (*receive_it)  (uint8_t *data, uint16_t length);
	int (*transmit_dma)(uint8_t *data, uint16_t length);
	int (*receive_dma) (uint8_t *data, uint16_t length);
};
#endif


#ifdef HAL_I2C_MODULE_ENABLED
struct i2c_api {
	I2C_HandleTypeDef *handle;
	void (*init)(void);
	int (*master_transmit)              (uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout);
	int (*master_receive)               (uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout);
	int (*master_transmit_it)           (uint16_t DevAddress, uint8_t *pData, uint16_t Size);
	int (*master_receive_it)            (uint16_t DevAddress, uint8_t *pData, uint16_t Size);
	int (*master_sequential_transmit_it)(uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t XferOptions);
	int (*master_sequential_receive_it) (uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t XferOptions);
	int (*master_transmit_dma)          (uint16_t DevAddress, uint8_t *pData, uint16_t Size);
	int (*master_receive_dma)           (uint16_t DevAddress, uint8_t *pData, uint16_t Size);
	
	int (*slave_transmit)              (uint8_t *pData, uint16_t Size, uint32_t Timeout);
	int (*slave_receive)               (uint8_t *pData, uint16_t Size, uint32_t Timeout);
	int (*slave_transmit_it)           (uint8_t *pData, uint16_t Size);
	int (*slave_receive_it)            (uint8_t *pData, uint16_t Size);
	int (*slave_sequential_transmit_it)(uint8_t *pData, uint16_t Size, uint32_t XferOptions);
	int (*slave_sequential_receive_it) (uint8_t *pData, uint16_t Size, uint32_t XferOptions);
	int (*slave_transmit_dma)          (uint8_t *pData, uint16_t Size);
	int (*slave_receive_dma)           (uint8_t *pData, uint16_t Size);
	
	void (*mem_write)   (uint8_t Addr, uint8_t Reg, uint8_t Value);
	uint8_t (*mem_read) (uint8_t Addr, uint8_t Reg);
	int (*mem_write_it) (uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size);
	int (*mem_read_it)  (uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size);
	int (*mem_write_dma)(uint8_t Addr, uint16_t Reg, uint8_t *pBuffer, uint16_t Length);
	int (*mem_read_dma) (uint8_t Addr, uint16_t Reg, uint8_t *pBuffer, uint16_t Length);
};
#endif


#ifdef HAL_SPI_MODULE_ENABLED
struct spi_api {
	SPI_HandleTypeDef *handle;
	void (*init)(void);
	int (*transmit)    ();
	int (*receive)     ();
	int (*transmit_it) ();
	int (*receive_it)  ();
	int (*transmit_dma)();
	int (*receive_dma) ();
};
#endif


#endif
