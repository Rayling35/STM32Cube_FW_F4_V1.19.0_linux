/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include "system_initialization.h"
#include "uart_printf.h"
#include "stm32f4xx_hal.h"
#include "device.h"
#include "pz_lcd_driver.h"
#include "api_lcd_common.h"
#include "main.h"


int main(void)
{
	system_initialization();
	uart_printf_init();
	
	struct device *Pz_lcd = pz_lcd_device_binding();
	struct lcd_value Voltage;
	struct lcd_value Current;
	struct lcd_value Power;
	struct lcd_value Consumption;
	
	lcd_init(Pz_lcd);
	printf("All device init finish\r\n");
	
	lcd_set_all(Pz_lcd);
	HAL_Delay(500);
	lcd_clean_all(Pz_lcd);
	HAL_Delay(500);
	
	Voltage.value_integer = 110;
	Voltage.value_decimal = 0;
	
	Current.value_integer = 13;
	Current.value_decimal = 94;
	
	Power.value_integer = 1533;
	Power.value_decimal = 4;
	
	Consumption.value_integer = 8549;
	Consumption.value_decimal = 0;
	
	lcd_value_send(Pz_lcd, LCD_PZ_VOLTAGE, &Voltage);
	lcd_value_send(Pz_lcd, LCD_PZ_CURRENT, &Current);
	lcd_value_send(Pz_lcd, LCD_PZ_POWER, &Power);
	lcd_value_send(Pz_lcd, LCD_PZ_CONSUMPTION, &Consumption);
	
	while(1) {
	}
}
