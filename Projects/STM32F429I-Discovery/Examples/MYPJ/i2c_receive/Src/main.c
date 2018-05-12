#include "system_initialization.h"
#include "uart_printf.h"
#include "main.h"

#include "api_define.h"
#include "i2c1.h"
#include "i2c3.h"


#define BME280_ADDRESS           0x76
#define BME280_CHIPID            0xD0

#define STMPE811_ADDRESS         0x41
#define STMPE811_REG_CHP_ID_LSB  0x00
#define STMPE811_REG_CHP_ID_MSB  0x01

int main(void)
{
	system_initialization();
	uart_printf_init();
	
	struct i2c_api *i2c1 = i2c1_binding();
	struct i2c_api *i2c3 = i2c3_binding();
	i2c1->init();
	i2c3->init();
	printf("I2C init\r\n");
	
	int status;
	uint8_t value_bme280 = 0;
	uint8_t value_lsb = 0;
	uint8_t value_msb = 0;
	
	while(1) {
		status = i2c3->mem_read(BME280_ADDRESS, BME280_CHIPID, &value_bme280, 1, 1);
		if(status != HAL_OK) {
			printf("BME280 mem_read fail! %d\r\n", status);
		}
		printf("BME280_0x60 == %X\r\n", value_bme280);
		
		
		status = i2c3->mem_read(STMPE811_ADDRESS, STMPE811_REG_CHP_ID_LSB, &value_lsb, 1, 1);
		if(status != HAL_OK) {
			printf("STMPE811_LSB mem_read fail! %d\r\n", status);
		}
		
		status = i2c3->mem_read(STMPE811_ADDRESS, STMPE811_REG_CHP_ID_MSB, &value_msb, 1, 1);
		if(status != HAL_OK) {
			printf("STMPE811_MSB mem_read fail! %d\r\n", status);
		}
		printf("STMPE811_0x0811 == %X\r\n", (value_lsb << 8) | value_msb);
		
		
		printf("\r\n");
		HAL_Delay(2000);
	}
}
