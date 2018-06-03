#include "ht1621_driver.h"
#include "seg7_common_api.h"
#include "pz_lcd_driver.h"
#include "lcd_common_api.h"


struct pz_lcd_data {
	struct device *ht1621;
};

struct pz_lcd_config {
	uint8_t config;
};


static void seg7(struct device *dev, uint16_t select, uint8_t a, uint8_t b, uint8_t c,
	               uint8_t d, uint8_t e, uint8_t f, uint8_t g, uint16_t function)
{
	struct pz_lcd_data *d_data = dev->data;
	
	if(select == 0 || select == 2 || select == 4 || select == 6 || select == 8 ||
		select == 10 || select == 12 || select == 14) {
			
			seg7_write_data_bit_4(d_data->ht1621, select+0, a, f, e, d);
			seg7_write_data_bit_4(d_data->ht1621, select+1, b, g, c, function);
			
	}else if(select == 16 || select == 18 || select == 20 || select == 22 || select == 24 ||
		select == 26 || select == 28 || select == 30) {
			
			seg7_write_data_bit_4(d_data->ht1621, select+0, d, e, f, a);
			seg7_write_data_bit_4(d_data->ht1621, select+1, function, c, g, b);
	}
}

/*-----------API--------------*/
static void show_display(struct device *dev, uint16_t select, uint8_t *number, uint16_t function)
{
	seg7(dev,select,number[0],number[1],number[2],number[3],number[4],number[5],number[6],function);
}

static void set_all_display(struct device *dev)
{
	struct pz_lcd_data *d_data = dev->data;
	uint16_t i;
	
	for(i = 0; i < 0x3F; i++) {                   //A5~A0: 00111111
		seg7_write_data_4(d_data->ht1621, i, 0x0F); //D3~D0: 00001111 set 1
	}
}

static void clean_all_display(struct device *dev)
{
	struct pz_lcd_data *d_data = dev->data;
	uint16_t i;
	
	for(i = 0; i < 0x3F; i++) {                   //A5~A0: 00111111
		seg7_write_data_4(d_data->ht1621, i, 0x00); //D3~D0: 00001111 set 0
	}
}

static const struct lcd_common_api pz_lcd_api = {
	.show      = show_display,
	.set_all   = set_all_display,
	.clean_all = clean_all_display,
};

static struct pz_lcd_data pz_lcd_data;

static const struct pz_lcd_config pz_lcd_config;

static int pz_lcd_dev_init(struct device *dev)
{
	struct pz_lcd_data *d_data = dev->data;
	
	d_data->ht1621 = ht1621_device_binding();
	seg7_init(d_data->ht1621);
	printf("PZ LCD device init\r\n");
	
	return 0;
}

struct device pz_lcd = {
	.api    = &pz_lcd_api,
	.data   = &pz_lcd_data,
	.config = &pz_lcd_config,
	.init   = pz_lcd_dev_init,
};

struct device* pz_lcd_device_binding(void)
{
	return &pz_lcd;
}
