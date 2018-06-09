#ifndef __HT1621_DRIVER_H
#define __HT1621_DRIVER_H

#include "stm32f4xx_hal.h"


struct ht1621_data {
	uint8_t data;
};

#define  BIAS          0x29
#define  RC256         0x18
#define  SYSEN         0x01
#define  LCDON         0x03

struct device* ht1621_device_binding(void);


#endif
