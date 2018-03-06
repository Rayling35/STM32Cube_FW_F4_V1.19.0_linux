#ifndef _IO_API_H_
#define _IO_API_H_

#include <dev.h>

               /*-----------API--------------*/
typedef int (*io_api_1)(struct device *dev, int len);

struct io_api {
	io_api_1 func;
};


               /*-----------APP--------------*/
static inline int io_func(struct device *dev, int len)
{
	const struct io_api *io_api = dev->api;
	return io_api->func(dev, len);
}

#endif
