#ifndef __SPI_DRIVER_H
#define __SPI_DRIVER_H


#ifdef SPI4_CS1
struct device* spi4_binding(void);
#endif

#ifdef SPI5_CS1
struct device* spi5_binding(void);
#endif


#endif
