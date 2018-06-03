#include "system_initialization.h"
#include "uart_printf.h"
#include "device.h"
#include "pz_lcd_driver.h"
#include "lcd_common_api.h"
#include "main.h"


int main(void)
{
	system_initialization();
	uart_printf_init();
	
	struct device *pz_lcd = pz_lcd_device_binding();
	lcd_init(pz_lcd);
	
	printf("All device init\r\n");
	
	lcd_set_all(pz_lcd);
	HAL_Delay(500);
	lcd_clean_all(pz_lcd);
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
		lcd_show(pz_lcd, 0, no0, 0);
		HAL_Delay(100);
		lcd_show(pz_lcd, 0, no1, 1);
		HAL_Delay(100);
		lcd_show(pz_lcd, 0, no2, 0);
		HAL_Delay(100);
		lcd_show(pz_lcd, 0, no3, 1);
		HAL_Delay(100);
		lcd_show(pz_lcd, 0, no4, 0);
		HAL_Delay(100);
		lcd_show(pz_lcd, 0, no5, 1);
		HAL_Delay(100);
		lcd_show(pz_lcd, 0, no6, 0);
		HAL_Delay(100);
		lcd_show(pz_lcd, 0, no7, 1);
		HAL_Delay(100);
		lcd_show(pz_lcd, 0, no8, 0);
		HAL_Delay(100);
		lcd_show(pz_lcd, 0, no9, 1);
		HAL_Delay(100);
	}
}
