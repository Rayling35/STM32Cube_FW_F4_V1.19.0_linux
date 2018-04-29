#include "system_initialization.h"
#include "uart_printf.h"
#include "main.h"

#include "api_define.h"
#include "i2c1.h"
#include "i2c3.h"


#define TS_I2C_ADDRESS          0x82
#define STMPE811_ID             0x0811

#define STMPE811_REG_CHP_ID_LSB         0x00
#define STMPE811_REG_CHP_ID_MSB         0x01

static uint8_t ReadData(struct i2c_api *hi2c, uint8_t Addr, uint8_t Reg)
{
	int status;
	uint8_t value = 0;
	
	status = hi2c->mem_read(Addr, Reg, &value, 1, 0x3000);
	if(status != 0) {
		printf("read fail!\r\n");
		printf("%d\r\n", status);
	}
	return value;
}

int main(void)
{
	system_initialization();
	uart_printf_init();
	
	struct i2c_api *i2c1 = i2c1_binding();
	struct i2c_api *i2c3 = i2c3_binding();
	i2c1->init();
	i2c3->init();
	printf("I2C init\r\n");
	
	printf("0x0811 == %X\r\n", ((ReadData(i2c3, TS_I2C_ADDRESS, STMPE811_REG_CHP_ID_LSB) << 8) |\
                              (ReadData(i2c3, TS_I2C_ADDRESS, STMPE811_REG_CHP_ID_MSB))));
}
