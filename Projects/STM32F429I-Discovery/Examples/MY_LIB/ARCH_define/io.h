#ifndef _IO_H_
#define _IO_H_

#include <dev.h>

/*-----------API--------------*/
typedef int (*io_api_1)(struct device *dev, int len);

struct io_api {
	io_api_1 print;
};

/*----------User-APP----------*/
static inline int io_print(struct device *dev, int len)
{
	const struct io_api *ptr_io_api = dev->api;
	return ptr_io_api->print(dev, len);
}

#endif
