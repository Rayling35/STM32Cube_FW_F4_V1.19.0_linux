#include "io_common_api.h"
#include "io_driver.h"

struct io_data {
	int mydata;
};

struct io_config {
	int cfg;
};

/*-----------API--------------*/
static int func_len(struct device *dev, int len)
{
	const struct io_config *config = dev->config;
	struct io_data *data = dev->data;

	data->mydata = len;
	printf("cfg=%d\r\n", config->cfg);
	return data->mydata;
}

static const struct io_common_api io0_driver_api = {
	.func = func_len,
};


#ifdef IO0
static struct io_data io0_data;

static const struct io_config io0_config = {
	.cfg = 7,
};

static int io0_init(struct device *dev)
{
	const struct io_config *config = dev->config;
	
	return config->cfg + 5;
}

struct device io_0 = {
	.api     = &io0_driver_api,
	.data   = &io0_data,
	.config = &io0_config,
	.init     = io0_init,
};

uint32_t io0_binding(void)
{
	return (uint32_t)&io_0;
}
#endif
