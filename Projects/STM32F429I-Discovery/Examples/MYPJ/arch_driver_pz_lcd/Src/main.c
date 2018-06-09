/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
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
	
	uint16_t voltage     = 110;
	float    current     = 13.94;
	float    power       = 1533.4;
	uint32_t consumption = 8549;
	
	pz_voltage(pz_lcd, voltage);
	pz_current(pz_lcd, current);
	pz_power(pz_lcd, power);
	pz_consumption(pz_lcd, consumption);
	
	while(1) {
	}
}
