#include "system_initialization.h"
#include "uart_printf.h"
#include "device.h"
#include "spi_driver.h"
#include "spi_common_api.h"
#include "main.h"


#define BME280_REG_ID               0xD0

#define L3GD20_RW                   0x80
#define L3GD20_MS                   0x00
#define L3GD20_WHO_AM_I_ADDR        0x0F | L3GD20_RW | L3GD20_MS

int main(void)
{
	system_initialization();
	uart_printf_init();
	
	struct device *spi4 = spi4_cs1_device_binding();
	struct device *spi5 = spi5_cs1_device_binding();
	spi_init(spi4);
	spi_init(spi5);
	printf("SPI device init\r\n");
	
	int status;
	uint8_t bme280_tx[2];
	uint8_t bme280_rx[2];
	uint8_t l3gd20_tx[2];
	uint8_t l3gd20_rx[2];
	
	bme280_tx[0] = BME280_REG_ID;
	l3gd20_tx[0] = L3GD20_WHO_AM_I_ADDR;
	
	while(1) {
		status = spi_transmit_receive(spi4, bme280_tx, bme280_rx, 2);
		if(status != HAL_OK) {
			printf("BME280 transfer fail! %d\r\n", status);
		}
		printf("BME280_0x60 == %X\r\n", bme280_rx[1]);
		
		status = spi_transmit_receive(spi5, l3gd20_tx, l3gd20_rx, 2);
		if(status != HAL_OK) {
			printf("L3GD20 transfer fail! %d\r\n", status);
		}
		printf("L3GD20_0xD4 == %X\r\n", l3gd20_rx[1]);
		
		printf("\r\n");
		HAL_Delay(2000);
	}
}