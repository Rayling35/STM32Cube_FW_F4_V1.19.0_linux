#include "system_initialization.h"
#include "uart_printf.h"
#include "device.h"
#include "spi_driver.h"
#include "spi_common_api.h"
#include "main.h"


int sample_register_write(struct device *spi, uint8_t reg, uint8_t *data, uint16_t length)
{
	uint8_t tx_data[length+1];
	uint8_t dummy;
	uint16_t i;
	
	tx_data[0] = reg;
	for(i = 1; i <= length; i++) {
		tx_data[i] = *data;
		data++;
	}
	return spi_transmit_receive(spi, tx_data, &dummy, length+1);
}

int sample_register_read(struct device *spi, uint8_t reg, uint8_t *data, uint16_t length)
{
	int status;
	uint16_t i;
	
	status = spi_transmit_receive(spi, &reg, data, length+1);
	for(i = 0; i < length; i++) {
		data[i] = data[i+1];
	}
	return status;
}

#define BME280_REG_ID               0xD0

#define L3GD20_R                    0x80
#define L3GD20_W                    0x00
#define L3GD20_MS                   0x00
#define L3GD20_WHO_AM_I_ADDR        0x0F
#define L3GD20_CTRL_REG1            0x20

int main(void)
{
	system_initialization();
	uart_printf_init();
	
	struct device *spi4 = spi4_cs1_device_binding();
	struct device *spi5 = spi5_cs1_device_binding();
	spi_init(spi4);
	spi_init(spi5);
	printf("SPI device init\r\n");
	
	uint8_t bme280_rx;
	
	uint8_t l3gd20_tx = 0x09;
	uint8_t l3gd20_rx;
	
	while(1) {
		sample_register_read(spi4, BME280_REG_ID, &bme280_rx, 1);
		printf("BME280_0x60 = %X\r\n", bme280_rx);
		
		sample_register_read(spi5, L3GD20_WHO_AM_I_ADDR|L3GD20_R|L3GD20_MS, &l3gd20_rx, 1);
		printf("L3GD20_0xD4 = %X\r\n", l3gd20_rx);
		
		sample_register_write(spi5, L3GD20_CTRL_REG1|L3GD20_W|L3GD20_MS, &l3gd20_tx, 1);
		sample_register_read(spi5, L3GD20_CTRL_REG1|L3GD20_R|L3GD20_MS, &l3gd20_rx, 1);
		printf("CTRL_REG1 = %X\r\n", l3gd20_rx);
		
		printf("\r\n");
		HAL_Delay(2000);
	}
}
