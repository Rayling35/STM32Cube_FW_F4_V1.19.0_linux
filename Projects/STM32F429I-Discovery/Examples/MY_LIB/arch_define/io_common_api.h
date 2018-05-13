#ifndef __IO_COMMON_API_H
#define __IO_COMMON_API_H

#include "device.h"


               /*-----------API--------------*/
typedef int (*io_api_1)(struct device *dev, int len);

struct io_common_api {
	io_api_1 func;
};


               /*-----------APP--------------*/
static inline int io_func(struct device *dev, int len)
{
	const struct io_common_api *io_api = dev->api;
	return io_api->func(dev, len);
}


#endif
