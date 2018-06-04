#include "api_define.h"
#include "spi_common_api.h"
#include "spi_driver.h"


struct spi_data {
	struct spi_api *spi_cs_hal;
};

struct spi_config {
	uint32_t tx_timeout;
	uint32_t rx_timeout;
	uint32_t tx_rx_timeout;
};


/*-----------API--------------*/

static int transmit_data(struct device *dev, uint8_t *tx_data, uint16_t length)
{
	struct spi_data *d_data           = dev->data;
	const struct spi_config *d_config = dev->config;
	struct spi_api *spi_cs_hal        = d_data->spi_cs_hal;
	
	return spi_cs_hal->transmit(tx_data, length, d_config->tx_timeout);
}

static int receive_data(struct device *dev, uint8_t *rx_data, uint16_t length)
{
	struct spi_data *d_data           = dev->data;
	const struct spi_config *d_config = dev->config;
	struct spi_api *spi_cs_hal        = d_data->spi_cs_hal;
	
	return spi_cs_hal->receive(rx_data, length, d_config->rx_timeout);
}

static int receive_data32(struct device *dev, uint32_t *rx_data, uint16_t length)
{
	struct spi_data *d_data           = dev->data;
	const struct spi_config *d_config = dev->config;
	struct spi_api *spi_cs_hal        = d_data->spi_cs_hal;
	
	return spi_cs_hal->receive32(rx_data, length, d_config->rx_timeout);
}

static int transmit_receive_data(struct device *dev, uint8_t *tx_data, uint8_t *rx_data, uint16_t length)
{
	struct spi_data *d_data           = dev->data;
	const struct spi_config *d_config = dev->config;
	struct spi_api *spi_cs_hal        = d_data->spi_cs_hal;
	
	return spi_cs_hal->transmit_receive(tx_data, rx_data, length, d_config->tx_rx_timeout);
}

static const struct spi_common_api spi_common_api = {
	.transmit         = transmit_data,
	.receive          = receive_data,
	.receive32        = receive_data32,
	.transmit_receive = transmit_receive_data,
};


#ifdef SPI4_CS1_DEV
#include "spi4_cs1.h"
static struct spi_data spi4_cs1_data;

static const struct spi_config spi4_cs1_config = {
	.tx_timeout    = 100,
	.rx_timeout    = 100,
	.tx_rx_timeout = 100,
};

static int spi4_cs1_dev_init(struct device *dev)
{
	struct spi_data *d_data = dev->data;
	
	d_data->spi_cs_hal = spi4_cs1_binding();
	d_data->spi_cs_hal->init();
	printf("SPI4_CS1 device init\r\n");
	
	return 0;
}

struct device spi_4_cs1 = {
	.api    = &spi_common_api,
	.data   = &spi4_cs1_data,
	.config = &spi4_cs1_config,
	.init   = spi4_cs1_dev_init,
};

struct device* spi4_cs1_device_binding(void)
{
	return &spi_4_cs1;
}
#endif

#ifdef SPI5_CS1_DEV
#include "spi5_cs1.h"
static struct spi_data spi5_cs1_data;

static const struct spi_config spi5_cs1_config = {
	.tx_timeout    = 100,
	.rx_timeout    = 100,
	.tx_rx_timeout = 100,
};

static int spi5_cs1_dev_init(struct device *dev)
{
	struct spi_data *d_data = dev->data;
	
	d_data->spi_cs_hal = spi5_cs1_binding();
	d_data->spi_cs_hal->init();
	printf("SPI5_CS1 device init\r\n");
	
	return 0;
}

struct device spi_5_cs1 = {
	.api    = &spi_common_api,
	.data   = &spi5_cs1_data,
	.config = &spi5_cs1_config,
	.init   = spi5_cs1_dev_init,
};

struct device* spi5_cs1_device_binding(void)
{
	return &spi_5_cs1;
}
#endif
