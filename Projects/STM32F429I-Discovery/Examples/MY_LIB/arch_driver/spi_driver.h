#ifndef __SPI_DRIVER_H
#define __SPI_DRIVER_H


#ifdef SPI4_CS1_DEV
struct device* spi4_cs1_device_binding(void);
#endif

#ifdef SPI5_CS1_DEV
struct device* spi5_cs1_device_binding(void);
#endif


#endif
