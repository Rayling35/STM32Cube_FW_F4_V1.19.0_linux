#include <io_api.h>
#include "io.h"

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

/*-------IO0 definition-------*/
#ifdef IO0
static const struct io_api io0_api = {
	.func = func_len,
};

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
	.data   = &io0_data,
	.api     = &io0_api,
	.config = &io0_config,
	.init     = io0_init,
};
#endif //IO0

