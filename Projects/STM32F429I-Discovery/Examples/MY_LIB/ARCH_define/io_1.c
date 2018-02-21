#include <io_api.h>
//#include "io_1.h" //external add..

struct io_data {
	int mydata;
};

struct io_config {
	int cfg;
};

/*-----------API--------------*/
static int print_len(struct device *dev, int len)
{
	const struct io_config *ptr_config = dev->config;
	struct io_data *ptr_data = dev->data;

	ptr_data->mydata = len;
	printf("cfg = %d\n", ptr_config->cfg);
	return ptr_data->mydata;
}

/*----------Define------------*/
static const struct io_api io_api_0 = {
	.print = print_len,
};

static struct io_data io_data_0;

static const struct io_config io_config_0 = {
	.cfg = 7,
};

static int io_init_0(struct device *dev)
{
	const struct io_config *ptr_config = dev->config;
	return ptr_config->cfg + 5;
}

struct device real_io_0 = {
	.data   = &io_data_0,
	.api     = &io_api_0,
	.config = &io_config_0,
	.init     = io_init_0,
};


