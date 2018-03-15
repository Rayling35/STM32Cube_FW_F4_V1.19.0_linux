#ifndef __THREAD2_H
#define __THREAD2_H

#include <stdio.h>
#include "cmsis_os.h"

void r_queue(void);
void message_put(uint16_t msg);

#endif
