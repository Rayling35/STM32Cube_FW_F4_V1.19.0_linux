#include "system_initialization.h"
#include "uart_printf.h"
#include "device.h"
#include "ht1621_driver.h"
#include "seg7_common_api.h"
#include "main.h"


void seg7(struct device *dev, uint16_t select, uint8_t a, uint8_t b, uint8_t c,
	        uint8_t d, uint8_t e, uint8_t f, uint8_t g, uint16_t function)
{
	if(select == 0 || select == 2 || select == 4 || select == 6 || select == 8 ||
		select == 10 || select == 12 || select == 14) {
			
			seg7_write_data_bit_4(dev, select+0, a, f, e, d);
			seg7_write_data_bit_4(dev, select+1, b, g, c, function);
			
	}else if(select == 16 || select == 18 || select == 20 || select == 22 || select == 24 ||
		select == 26 || select == 28 || select == 30) {
			
			seg7_write_data_bit_4(dev, select+0, d, e, f, a);
			seg7_write_data_bit_4(dev, select+1, function, c, g, b);
	}
}

/* number[7]: abcdefg */
void seg7_show(struct device *dev, uint16_t select, uint8_t *number, uint16_t function)
{
	seg7(dev,select,number[0],number[1],number[2],number[3],number[4],number[5],number[6],function);
}

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
	
	printf("LCD device init\r\n");
	
	
	seg7_set_all(ht1621);
	HAL_Delay(500);
	seg7_clean_all(ht1621);
	HAL_Delay(500);
	
	//abcdefg
	uint8_t no0[7] = {1,1,1,1,1,1,0}; //0
	uint8_t no1[7] = {0,1,1,0,0,0,0}; //1
	uint8_t no2[7] = {1,1,0,1,1,0,1}; //2
	uint8_t no3[7] = {1,1,1,1,0,0,1}; //3
	uint8_t no4[7] = {0,1,1,0,0,1,1}; //4
	uint8_t no5[7] = {1,0,1,1,0,1,1}; //5
	uint8_t no6[7] = {1,0,1,1,1,1,1}; //6
	uint8_t no7[7] = {1,1,1,0,0,1,0}; //7
	uint8_t no8[7] = {1,1,1,1,1,1,1}; //8
	uint8_t no9[7] = {1,1,1,1,0,1,1}; //9
	
	while(1) {
		seg7_show(ht1621, 0, no0, 0);
		HAL_Delay(100);
		seg7_show(ht1621, 0, no1, 1);
		HAL_Delay(100);
		seg7_show(ht1621, 0, no2, 0);
		HAL_Delay(100);
		seg7_show(ht1621, 0, no3, 1);
		HAL_Delay(100);
		seg7_show(ht1621, 0, no4, 0);
		HAL_Delay(100);
		seg7_show(ht1621, 0, no5, 1);
		HAL_Delay(100);
		seg7_show(ht1621, 0, no6, 0);
		HAL_Delay(100);
		seg7_show(ht1621, 0, no7, 1);
		HAL_Delay(100);
		seg7_show(ht1621, 0, no8, 0);
		HAL_Delay(100);
		seg7_show(ht1621, 0, no9, 1);
		HAL_Delay(100);
	}
}
