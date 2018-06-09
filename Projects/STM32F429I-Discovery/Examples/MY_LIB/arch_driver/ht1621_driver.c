/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include "gpio_driver.h"
#include "gpio_common_api.h"
#include "ht1621.h"
#include "ht1621_driver.h"
#include "seg7_common_api.h"


static void command(struct device *dev, uint8_t cmd)
{
	send_command(cmd);
}

static void write_data_4(struct device *dev, uint8_t seg_addr, uint8_t com_data)
{
	write_seg_data_4(seg_addr, com_data);
}

static void write_data_44(struct device *dev, uint8_t seg_addr, uint8_t *com_data, uint16_t count)
{
	write_seg_data_44(seg_addr, com_data, count);
}

static void write_data_bit_4(struct device *dev, uint8_t seg_addr, uint8_t d3, uint8_t d2, uint8_t d1, uint8_t d0)
{
	write_seg_data_bit_4(seg_addr, d3, d2, d1, d0);
}

static const struct seg7_common_api ht1621_api = {
	.write_command    = command,
	.write_data_4     = write_data_4,
	.write_data_8     = write_data_44,
	.write_data_bit_4 = write_data_bit_4,
};

static struct ht1621_data ht1621_data;

static int ht1621_dev_init(struct device *dev)
{
	struct device *gpio_a5 = gpio_a5_device_binding();
	struct device *gpio_g2 = gpio_g2_device_binding();
	struct device *gpio_g3 = gpio_g3_device_binding();
	
	gpio_init(gpio_a5);
	gpio_init(gpio_g2);
	gpio_init(gpio_g3);
	ht1621_init();
	printf("HT1621 device init\r\n");
	
	return 0;
}

struct device ht1621 = {
	.api    = &ht1621_api,
	.data   = &ht1621_data,
	.init   = ht1621_dev_init,
};

struct device* ht1621_device_binding(void)
{
	return &ht1621;
}
