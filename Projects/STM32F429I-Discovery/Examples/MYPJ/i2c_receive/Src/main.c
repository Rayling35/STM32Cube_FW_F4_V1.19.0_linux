#include "system_initialization.h"
#include "uart_printf.h"
#include "main.h"

#include "api_define.h"
#include "i2c3.h"


#define IO_I2C_ADDRESS              0x82
#define STMPE811_REG_CHP_ID_LSB     0x00
#define STMPE811_REG_CHP_ID_MSB     0x01

int main(void)
{
	system_initialization();
	uart_printf_init();
	
	struct i2c_api *i2c3 = i2c3_binding();
	i2c3->init();
	
	uint16_t lsb_id = i2c3->mem_read(IO_I2C_ADDRESS, STMPE811_REG_CHP_ID_LSB);
	uint16_t msb_id = i2c3->mem_read(IO_I2C_ADDRESS, STMPE811_REG_CHP_ID_MSB);
	printf("ID:%d\r\n", (lsb_id << 8) | msb_id);
}
