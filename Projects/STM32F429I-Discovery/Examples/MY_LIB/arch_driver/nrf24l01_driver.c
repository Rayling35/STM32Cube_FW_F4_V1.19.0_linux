#include "rf_common_api.h"
#include "nrf24l01_driver.h"
#include "spi_common_api.h"
#include "gpio_common_api.h"


struct nrf24l01_data {
	struct device *spi;
	struct device *gpio;
	int data1;
	int data2;
};

struct nrf24l01_config {
	uint32_t this_config_1;
	uint32_t this_config_2;
};


/*-----------API--------------*/
static int send_data(struct device *dev)
{
	struct nrf24l01_data *data = dev->data;
	//const struct nrf24l01_config *config = dev->config;
	struct device *spi         = data->spi;
	uint8_t tx[3];
	uint8_t rx[3];
	int status;
	
	tx[0] = READ_REG_NRF24L01;
	tx[1] = STATUS;
	status = spi_transmit_receive(spi, tx, rx, 3);
	printf("spi_transmit_receive Status %d\r\n", status);
	printf("%X %X %X\r\n", rx[0], rx[1], rx[2]);
	
	return 0;
}

static int get_data(struct device *dev)
{
	return 0;
}

static const struct rf_common_api nrf24l01_api = {
	.send = send_data,
	.get  = get_data,
};

#include "spi_driver.h"
#include "gpio_driver.h"
static struct nrf24l01_data nrf24l01_data;

static const struct nrf24l01_config nrf24l01_config = {
	.this_config_1 = 100,
	.this_config_2 = 100,
};

static int nrf24l01_init(struct device *dev)
{
	struct nrf24l01_data *data = dev->data;
	
	data->spi  = spi4_cs1_device_binding();
	data->gpio = gpio_a0_device_binding();
	spi_init(data->spi);
	gpio_init(data->gpio);
	printf("NRF24L01 device init\r\n");
	
	return 0;
}

struct device nrf24l01 = {
	.api    = &nrf24l01_api,
	.data   = &nrf24l01_data,
	.config = &nrf24l01_config,
	.init   = nrf24l01_init,
};

struct device* nrf24l01_device_binding(void)
{
	return &nrf24l01;
}


void a0_exit_handel(void)
{
	printf("NRF24L01 IRQ handel\r\n");
}
