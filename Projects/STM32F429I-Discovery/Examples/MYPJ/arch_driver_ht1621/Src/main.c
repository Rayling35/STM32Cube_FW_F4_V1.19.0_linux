#include "system_initialization.h"
#include "uart_printf.h"
#include "device.h"
#include "ht1621_driver.h"
#include "seg7_common_api.h"
#include "main.h"


void seg7_set_all(struct device *dev)
{
	uint16_t i;
	for(i = 0; i < 0x3F; i++) {        //A5~A0: 00111111
		seg7_write_data_4(dev, i, 0x0F); //D3~D0: 00001111 set 1
	}
}

void seg7_clean_all(struct device *dev)
{
	uint16_t i;
	for(i = 0; i < 0x3F; i++) {        //A5~A0: 00111111
		seg7_write_data_4(dev, i, 0x00); //D3~D0: 00001111 set 0
	}
}

int main(void)
{
	system_initialization();
	uart_printf_init();
	
	struct device *ht1621 = ht1621_device_binding();
	
	seg7_init(ht1621);
	
	seg7_write_command(ht1621, BIAS);
	seg7_write_command(ht1621, RC256);
	seg7_write_command(ht1621, SYSEN);
	seg7_write_command(ht1621, LCDON);
	
	printf("All device init\r\n");
	
	seg7_set_all(ht1621);
	HAL_Delay(500);
	seg7_clean_all(ht1621);
	HAL_Delay(500);
	
	uint16_t i;
	
	while(1) {
		for(i = 0; i < 32; i++) {
			seg7_write_data_4(ht1621, i, 0x01); //COM:0001
			HAL_Delay(100);
		}
		
		for(i = 0; i < 32; i++) {
			seg7_write_data_4(ht1621, i, 0x03); //COM:0011
			HAL_Delay(100);
		}
		
		for(i = 0; i < 32; i++) {
			seg7_write_data_4(ht1621, i, 0x07); //COM:0111
			HAL_Delay(100);
		}
		
		for(i = 0; i < 32; i++) {
			seg7_write_data_4(ht1621, i, 0x0F); //COM:1111
			HAL_Delay(100);
		}
		
		for(i = 0; i < 32; i++) {
			seg7_write_data_bit_4(ht1621, i, 1, 1, 1, 0); //COM:1110
			HAL_Delay(100);
		}
		
		for(i = 0; i < 32; i++) {
			seg7_write_data_bit_4(ht1621, i, 1, 1, 0, 0); //COM:1100
			HAL_Delay(100);
		}
		
		for(i = 0; i < 32; i++) {
			seg7_write_data_bit_4(ht1621, i, 1, 0, 0, 0); //COM:1000
			HAL_Delay(100);
		}
		
		for(i = 0; i < 32; i++) {
			seg7_write_data_bit_4(ht1621, i, 0, 0, 0, 0); //COM:0000
			HAL_Delay(100);
		}
	}
}