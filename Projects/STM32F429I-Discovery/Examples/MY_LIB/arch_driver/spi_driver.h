/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#ifndef __SPI_DRIVER_H
#define __SPI_DRIVER_H


struct spi_data {
	struct spi_api *spi_cs_hal;
};

struct spi_config {
	uint32_t tx_timeout;
	uint32_t rx_timeout;
	uint32_t tx_rx_timeout;
};

#ifdef SPI4_CS1_DEV
struct device* spi4_cs1_device_binding(void);
#endif

#ifdef SPI5_CS1_DEV
struct device* spi5_cs1_device_binding(void);
#endif


#endif
