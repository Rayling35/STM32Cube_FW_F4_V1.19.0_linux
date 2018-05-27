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


static int spi_register_write(struct device *spi, uint8_t reg, uint8_t *data, uint16_t length)
{
	uint8_t status;
	uint8_t uint8_t_ctr;
	
	status = spi_transmit_receive(spi, reg);
	
	for(uint8_t_ctr = 0; uint8_t_ctr < length; uint8_t_ctr++) {
		spi_transmit_receive(spi, *data++);
	}
	return status;
}

static int spi_register_read(struct device *spi, uint8_t reg, uint8_t *data, uint16_t length)
{
	uint8_t status;
	uint8_t uint8_t_ctr;
	
	status = spi_transmit_receive(spi, reg);
	
	for(uint8_t_ctr = 0; uint8_t_ctr < length; uint8_t_ctr++) {
		data[uint8_t_ctr] = spi_transmit_receive(spi, 0XFF);
	}
	return status;
}

/*-----------API--------------*/
static int send_data(struct device *dev)
{
	struct nrf24l01_data *data = dev->data;
	//const struct nrf24l01_config *config = dev->config;
	struct device *spi         = data->spi;
	uint8_t tx[6];
	uint8_t rx[6];
	int status;
	
	tx[0] = WRITE_REG_NRF24L01 + TX_ADDR;
	tx[1] = 0xA5;
	tx[2] = 0xA5;
	tx[3] = 0xA5;
	tx[4] = 0xA5;
	tx[5] = 0xA5;
	status = spi_transmit_receive(spi, tx, rx, 1);
	printf("%d\r\n", status);
	status = spi_transmit_receive(spi, tx+1, rx, 5);
	printf("%d\r\n", status);
	printf("%X\r\n", rx[0]);
	
	tx[0] = READ_REG_NRF24L01 + TX_ADDR;
	status = spi_transmit_receive(spi, tx, rx, 1);
	printf("%d\r\n", status);
	status = spi_transmit_receive(spi, tx, rx, 5);
	printf("%d\r\n", status);
	printf("%X %X %X %X %X\r\n", rx[1], rx[2], rx[3], rx[4], rx[5]);
	
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
