#ifndef __UART_DRIVER_H
#define __UART_DRIVER_H


#ifdef UART3_DEV
struct device* uart3_device_binding(void);
#endif

#ifdef UART6_DEV
struct device* uart6_device_binding(void);
#endif

#ifdef UART7_DEV
struct device* uart7_device_binding(void);
#endif


#endif
