#include "standard_common_api.h"
#include "template_driver.h"
#include "device_1_common_api.h"
#include "device_2_common_api.h"


struct template_data {
	struct device *binding_device_1;
	struct device *binding_device_2;
	int data1;
	int data2;
};

struct template_config {
	uint32_t this_config_1;
	uint32_t this_config_2;
};


/*-----------API--------------*/
static int send_data(struct device *dev, uint8_t *tx_data, uint16_t length)
{
	struct template_data *data           = dev->data;
	const struct template_config *config = dev->config;
	struct device *binding_dev_1         = data->binding_device_1;
	struct device *binding_dev_2         = data->binding_device_2;
	
	binding_1_app(binding_dev_1, data->data1, config->this_config_1);
	binding_2_app(binding_dev_2, data->data1, config->this_config_1);
	
	return 0;
}

static int get_data(struct device *dev, uint8_t *rx_data, uint16_t length)
{
	struct template_data *data           = dev->data;
	const struct template_config *config = dev->config;
	struct device *binding_dev_1         = data->binding_device_1;
	struct device *binding_dev_2         = data->binding_device_2;
	
	binding_1_app(binding_dev_1, data->data2, config->this_config_2);
	binding_2_app(binding_dev_2, data->data2, config->this_config_2);
	
	return 0;
}

static const struct standard_common_api standard_common_api = {
	.send = send_data,
	.get  = get_data,
};


#include "device_1.h"
#include "device_2.h"
static struct template_data template_data;

static const struct template_config template_config = {
	.this_config_1 = 100,
	.this_config_2 = 100,
};

static int template_init(struct device *dev)
{
	struct template_data *data = dev->data;
	
	data->binding_device_1 = device_1_binding();
	data->binding_device_2 = device_2_binding();
	data->binding_device_1->init();
	data->binding_device_2->init();
	printf("TEMPLATE device init\r\n");
	
	return 0;
}

struct device template = {
	.api    = &template_common_api,
	.data   = &template_data,
	.config = &template_config,
	.init   = template_init,
};

struct device* template_device_binding(void)
{
	return &template;
}
