#include <dev.h>
#include <io.h>

struct config {
	int cfg;
};

struct data {
	int mydata;
};

static struct data io_data_0;

/*-----------API--------------*/
static int print_len(struct device *dev, int len)
{
	const struct config *ptr_config = dev->config;
	struct data *ptr_data = dev->data;

	ptr_data->mydata = len;
	printf("cfg = %d\n", ptr_config->cfg);
	return ptr_data->mydata;
}

static const struct io_api io_api_0 = {
	.print = print_len,
};

/*-------------------------*/
static const struct config io_config_0 = {
	.cfg = 7,
};

static int io_init_0(struct device *dev)
{
	const struct config *ptr_config = dev->config;
	return ptr_config->cfg + 5;
}

struct device real_io_0 = {
	.data   = &io_data_0,
	.api     = &io_api_0,
	.config = &io_config_0,
	.init     = io_init_0,
};


