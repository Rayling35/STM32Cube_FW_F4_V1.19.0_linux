#include "spi_common_api.h"
#include "api_define.h"
#include "spi_driver.h"


struct spi_data {
	struct spi_api *spi_cs_api;
};

struct spi_config {
	uint32_t rx_timeout;
	uint32_t tx_timeout;
	uint32_t tx_rx_timeout;
};

/*-----------API--------------*/
static int transmit_data(struct device *dev, uint8_t *tx_data, uint16_t length)
{
	struct spi_data *data           = dev->data;
	const struct spi_config *config = dev->config;
	struct spi_api *spi_cs_api      = data->spi_cs_api;
	
	return spi_cs_api->transmit(tx_data, length, config->tx_timeout);
}

static int receive_data(struct device *dev, uint8_t *rx_data, uint16_t length)
{
	struct spi_data *data           = dev->data;
	const struct spi_config *config = dev->config;
	struct spi_api *spi_cs_api      = data->spi_cs_api;
	
	return spi_cs_api->receive(rx_data, length, config->rx_timeout);
}

static int transmit_receive_data(struct device *dev, uint8_t *tx_data, uint8_t *rx_data, uint16_t length)
{
	struct spi_data *data           = dev->data;
	const struct spi_config *config = dev->config;
	struct spi_api *spi_cs_api      = data->spi_cs_api;
	
	return spi_cs_api->transmit_receive(tx_data, rx_data, length, config->tx_rx_timeout);
}

static const struct spi_common_api spi_driver_api = {
	.transmit         = transmit_data,
	.receive          = receive_data,
	.transmit_receive = transmit_receive_data
};


#ifdef SPI4_CS1
#include "spi4_cs1.h"
static struct spi_data spi4_cs1_data;
static const struct spi_config spi4_cs1_config = {
	.tx_timeout    = 1,
	.rx_timeout    = 1,
	.tx_rx_timeout = 1
};

static int spi4_cs1_init(struct device *dev)
{
	struct spi_data *data = dev->data;
	
	data->spi_cs_api = spi4_cs1_binding();
	return 0;
}

struct device spi_4_cs1 = {
	.api    = &spi_driver_api,
	.data   = &spi4_cs1_data,
	.config = &spi4_cs1_config,
	.init   = spi4_cs1_init,
};

struct device* spi4_cs1_device_binding(void)
{
	return &spi_4_cs1;
}
#endif

#ifdef SPI5_CS1
#include "spi5_cs1.h"
static struct spi_data spi5_cs1_data;
static const struct spi_config spi5_cs1_config = {
	.tx_timeout    = 1,
	.rx_timeout    = 1,
	.tx_rx_timeout = 1
};

static int spi5_cs1_init(struct device *dev)
{
	struct spi_data *data = dev->data;
	
	data->spi_cs_api = spi5_cs1_binding();
	return 0;
}

struct device spi_5_cs1 = {
	.api    = &spi_driver_api,
	.data   = &spi5_cs1_data,
	.config = &spi5_cs1_config,
	.init   = spi5_cs1_init,
};

struct device* spi5_cs1_device_binding(void)
{
	return &spi_5_cs1;
}
#endif
