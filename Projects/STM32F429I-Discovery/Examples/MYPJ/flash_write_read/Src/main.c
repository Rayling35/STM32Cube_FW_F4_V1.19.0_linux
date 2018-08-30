/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include "system_initialization.h"
#include "stm32f4xx_hal.h"
#include "uart_printf.h"
#include "flash_internal.h"
#include "main.h"


int main(void)
{
	system_initialization();
	uart_printf_init();
	
//	flash_internal_erase(SECTOR_0_16KB_8000000);
//	flash_internal_write(SECTOR_0_16KB_8000000, 0, 01);
//	flash_internal_write(SECTOR_0_16KB_8000000, 16383, 02);
//	printf("%d\r\n", flash_internal_read(SECTOR_0_16KB_8000000, 0));
//	printf("%d\r\n", flash_internal_read(SECTOR_0_16KB_8000000, 16383));
	
	flash_internal_erase(SECTOR_1_16KB_8004000);
	flash_internal_write(SECTOR_1_16KB_8004000, 0, 11);
	flash_internal_write(SECTOR_1_16KB_8004000, 16383, 12);
	printf("%d\r\n", flash_internal_read(SECTOR_1_16KB_8004000, 0));
	printf("%d\r\n", flash_internal_read(SECTOR_1_16KB_8004000, 16383));
	
	flash_internal_erase(SECTOR_2_16KB_8008000);
	flash_internal_write(SECTOR_2_16KB_8008000, 0, 21);
	flash_internal_write(SECTOR_2_16KB_8008000, 16383, 22);
	printf("%d\r\n", flash_internal_read(SECTOR_2_16KB_8008000, 0));
	printf("%d\r\n", flash_internal_read(SECTOR_2_16KB_8008000, 16383));
	
	flash_internal_erase(SECTOR_3_16KB_800C000);
	flash_internal_write(SECTOR_3_16KB_800C000, 0, 31);
	flash_internal_write(SECTOR_3_16KB_800C000, 16383, 32);
	printf("%d\r\n", flash_internal_read(SECTOR_3_16KB_800C000, 0));
	printf("%d\r\n", flash_internal_read(SECTOR_3_16KB_800C000, 16383));
	
	flash_internal_erase(SECTOR_4_64KB_8010000);
	flash_internal_write(SECTOR_4_64KB_8010000, 0, 41);
	flash_internal_write(SECTOR_4_64KB_8010000, 65535, 42);
	printf("%d\r\n", flash_internal_read(SECTOR_4_64KB_8010000, 0));
	printf("%d\r\n", flash_internal_read(SECTOR_4_64KB_8010000, 65535));
	
	flash_internal_erase(SECTOR_5_128KB_8020000);
	flash_internal_write(SECTOR_5_128KB_8020000, 0, 51);
	flash_internal_write(SECTOR_5_128KB_8020000, 131071, 52);
	printf("%d\r\n", flash_internal_read(SECTOR_5_128KB_8020000, 0));
	printf("%d\r\n", flash_internal_read(SECTOR_5_128KB_8020000, 131071));
	
	flash_internal_erase(SECTOR_6_128KB_8040000);
	flash_internal_write(SECTOR_6_128KB_8040000, 0, 61);
	flash_internal_write(SECTOR_6_128KB_8040000, 131071, 62);
	printf("%d\r\n", flash_internal_read(SECTOR_6_128KB_8040000, 0));
	printf("%d\r\n", flash_internal_read(SECTOR_6_128KB_8040000, 131071));
	
	flash_internal_erase(SECTOR_7_128KB_8060000);
	flash_internal_write(SECTOR_7_128KB_8060000, 0, 71);
	flash_internal_write(SECTOR_7_128KB_8060000, 131071, 72);
	printf("%d\r\n", flash_internal_read(SECTOR_7_128KB_8060000, 0));
	printf("%d\r\n", flash_internal_read(SECTOR_7_128KB_8060000, 131071));
	
	flash_internal_erase(SECTOR_8_128KB_8080000);
	flash_internal_write(SECTOR_8_128KB_8080000, 0, 81);
	flash_internal_write(SECTOR_8_128KB_8080000, 131071, 82);
	printf("%d\r\n", flash_internal_read(SECTOR_8_128KB_8080000, 0));
	printf("%d\r\n", flash_internal_read(SECTOR_8_128KB_8080000, 131071));
	
	flash_internal_erase(SECTOR_9_128KB_80A0000);
	flash_internal_write(SECTOR_9_128KB_80A0000, 0, 91);
	flash_internal_write(SECTOR_9_128KB_80A0000, 131071, 92);
	printf("%d\r\n", flash_internal_read(SECTOR_9_128KB_80A0000, 0));
	printf("%d\r\n", flash_internal_read(SECTOR_9_128KB_80A0000, 131071));
	
	flash_internal_erase(SECTOR_10_128KB_80C0000);
	flash_internal_write(SECTOR_10_128KB_80C0000, 0, 101);
	flash_internal_write(SECTOR_10_128KB_80C0000, 131071, 102);
	printf("%d\r\n", flash_internal_read(SECTOR_10_128KB_80C0000, 0));
	printf("%d\r\n", flash_internal_read(SECTOR_10_128KB_80C0000, 131071));
	
	flash_internal_erase(SECTOR_11_128KB_80E0000);
	flash_internal_write(SECTOR_11_128KB_80E0000, 0, 111);
	flash_internal_write(SECTOR_11_128KB_80E0000, 131071, 112);
	printf("%d\r\n", flash_internal_read(SECTOR_11_128KB_80E0000, 0));
	printf("%d\r\n", flash_internal_read(SECTOR_11_128KB_80E0000, 131071));
	
	flash_internal_erase(SECTOR_12_16KB_8100000);
	flash_internal_write(SECTOR_12_16KB_8100000, 0x0, 121);
	flash_internal_write(SECTOR_12_16KB_8100000, 0x3FFF, 122);
	printf("%d\r\n", flash_internal_read(SECTOR_12_16KB_8100000, 0x0));
	printf("%d\r\n", flash_internal_read(SECTOR_12_16KB_8100000, 0x3FFF));
	
	flash_internal_erase(SECTOR_13_16KB_8104000);
	flash_internal_write(SECTOR_13_16KB_8104000, 0x0, 131);
	flash_internal_write(SECTOR_13_16KB_8104000, 0x3FFF, 132);
	printf("%d\r\n", flash_internal_read(SECTOR_13_16KB_8104000, 0x0));
	printf("%d\r\n", flash_internal_read(SECTOR_13_16KB_8104000, 0x3FFF));
	
	flash_internal_erase(SECTOR_14_16KB_8108000);
	flash_internal_write(SECTOR_14_16KB_8108000, 0x0, 141);
	flash_internal_write(SECTOR_14_16KB_8108000, 0x3FFF, 142);
	printf("%d\r\n", flash_internal_read(SECTOR_14_16KB_8108000, 0x0));
	printf("%d\r\n", flash_internal_read(SECTOR_14_16KB_8108000, 0x3FFF));
	
	flash_internal_erase(SECTOR_15_16KB_810C000);
	flash_internal_write(SECTOR_15_16KB_810C000, 0x0, 151);
	flash_internal_write(SECTOR_15_16KB_810C000, 0x3FFF, 152);
	printf("%d\r\n", flash_internal_read(SECTOR_15_16KB_810C000, 0x0));
	printf("%d\r\n", flash_internal_read(SECTOR_15_16KB_810C000, 0x3FFF));
	
	flash_internal_erase(SECTOR_16_64KB_8110000);
	flash_internal_write(SECTOR_16_64KB_8110000, 0x0, 161);
	flash_internal_write(SECTOR_16_64KB_8110000, 0xFFFF, 162);
	printf("%d\r\n", flash_internal_read(SECTOR_16_64KB_8110000, 0x0));
	printf("%d\r\n", flash_internal_read(SECTOR_16_64KB_8110000, 0xFFFF));
	
	flash_internal_erase(SECTOR_17_128KB_8120000);
	flash_internal_write(SECTOR_17_128KB_8120000, 0x0, 171);
	flash_internal_write(SECTOR_17_128KB_8120000, 0x1FFFF, 172);
	printf("%d\r\n", flash_internal_read(SECTOR_17_128KB_8120000, 0x0));
	printf("%d\r\n", flash_internal_read(SECTOR_17_128KB_8120000, 0x1FFFF));
	
	flash_internal_erase(SECTOR_18_128KB_8140000);
	flash_internal_write(SECTOR_18_128KB_8140000, 0x0, 181);
	flash_internal_write(SECTOR_18_128KB_8140000, 0x1FFFF, 182);
	printf("%d\r\n", flash_internal_read(SECTOR_18_128KB_8140000, 0x0));
	printf("%d\r\n", flash_internal_read(SECTOR_18_128KB_8140000, 0x1FFFF));
	
	flash_internal_erase(SECTOR_19_128KB_8160000);
	flash_internal_write(SECTOR_19_128KB_8160000, 0x0, 191);
	flash_internal_write(SECTOR_19_128KB_8160000, 0x1FFFF, 192);
	printf("%d\r\n", flash_internal_read(SECTOR_19_128KB_8160000, 0x0));
	printf("%d\r\n", flash_internal_read(SECTOR_19_128KB_8160000, 0x1FFFF));
	
	flash_internal_erase(SECTOR_20_128KB_8180000);
	flash_internal_write(SECTOR_20_128KB_8180000, 0x0, 201);
	flash_internal_write(SECTOR_20_128KB_8180000, 0x1FFFF, 202);
	printf("%d\r\n", flash_internal_read(SECTOR_20_128KB_8180000, 0x0));
	printf("%d\r\n", flash_internal_read(SECTOR_20_128KB_8180000, 0x1FFFF));
	
	flash_internal_erase(SECTOR_21_128KB_81A0000);
	flash_internal_write(SECTOR_21_128KB_81A0000, 0x0, 211);
	flash_internal_write(SECTOR_21_128KB_81A0000, 0x1FFFF, 212);
	printf("%d\r\n", flash_internal_read(SECTOR_21_128KB_81A0000, 0x0));
	printf("%d\r\n", flash_internal_read(SECTOR_21_128KB_81A0000, 0x1FFFF));
	
	flash_internal_erase(SECTOR_22_128KB_81C0000);
	flash_internal_write(SECTOR_22_128KB_81C0000, 0x0, 221);
	flash_internal_write(SECTOR_22_128KB_81C0000, 0x1FFFF, 222);
	printf("%d\r\n", flash_internal_read(SECTOR_22_128KB_81C0000, 0x0));
	printf("%d\r\n", flash_internal_read(SECTOR_22_128KB_81C0000, 0x1FFFF));
	
	flash_internal_erase(SECTOR_23_128KB_81E0000);
	flash_internal_write(SECTOR_23_128KB_81E0000, 0x0, 231);
	flash_internal_write(SECTOR_23_128KB_81E0000, 0x1FFFF, 232);
	printf("%d\r\n", flash_internal_read(SECTOR_23_128KB_81E0000, 0x0));
	printf("%d\r\n", flash_internal_read(SECTOR_23_128KB_81E0000, 0x1FFFF));
}
